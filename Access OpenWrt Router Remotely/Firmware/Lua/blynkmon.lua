#!/usr/bin/env lua

local socket = require("socket")
local use_ssl, ssl = pcall(require, "ssl")

local Blynk = require("blynk.socket")
local Timer = require("timer")
local http = require("socket.http")

local template_id = "TMPxxxxxx"
local template_name = "Device"
local auth = "YourAuthToken"

local blynk = Blynk.new(auth, {
  heartbeat = 50,
  -- log = print,
})

function exec_out(cmd)
  local file = io.popen(cmd)
  if not file then return nil end
  local data = file:read("*a")
  file:close()
  -- print("Run: "..cmd.." -> "..data)
  return data
end

function read_file(path)
  local file = io.open(path, "rb")
  if not file then return nil end
  local data = file:read("*a")
  file:close()
  -- print("Read: "..path.." -> "..data)
  return data
end

function getArpClients()
  return tonumber(exec_out("cat /proc/net/arp | grep br-lan | grep 0x2 | wc -l"))
end

function getUptime()
  return tonumber(exec_out("cat /proc/uptime | awk '{print $1}'"))
end

function getWanIF()
  return exec_out("source /lib/functions/network.sh; network_flush_cache; network_find_wan NET_IF; echo -n $NET_IF")
end

function getWanIP()
  local wanif = getWanIF()
  if wanif == "" then return "" end
  return exec_out("source /lib/functions/network.sh; network_get_ipaddr NET_ADDR " .. wanif .. "; echo $NET_ADDR")
end

function getPublicIP()
  local body, code, headers, status = http.request("https://api.ipify.org")
  if code == 200 then
    return body
  end
  return ""
end

function getHddSpinning()
  local code = os.execute("smartctl --nocheck=standby --info /dev/sda > /dev/null")
  return (code == 0) and 1 or 0
end

function getHddStats()
  local out = exec_out("cat /proc/diskstats | grep 'sda ' | awk '{print $6, $10}'")
  local reads, writes = out:match("([^ ]+) +([^ ]+)")
  return reads, writes
end

function getCpuLoad()
  return tonumber(exec_out("top -bn1 | grep 'CPU:' | head -n1 | awk '{print $2+$4}'"))
end

function getRamUsage()
  return tonumber(exec_out("free | grep Mem | awk '{print ($2-$4)/$2 * 100.0}'"))
end

function getWanRxBytes()
  local wanif = getWanIF()
  if wanif == "" then return 0 end
  return tonumber(read_file("/sys/class/net/" .. wanif .. "/statistics/rx_bytes"))
end

function getWanTxBytes()
  local wanif = getWanIF()
  if wanif == "" then return 0 end
  return tonumber(read_file("/sys/class/net/" .. wanif .. "/statistics/tx_bytes"))
end

function getActiveConnections()
  return tonumber(read_file("/proc/sys/net/netfilter/nf_conntrack_count"))
end

function getWiFiStatus()
  if string.find(exec_out("ubus call network.wireless status | jsonfilter -e '@.radio0.up'"), "true") then
    return 1
  else
    return 0
  end
end

local function connectBlynk()
  local host = "blynk.cloud"

  local sock = assert(socket.tcp())
  sock:setoption("tcp-nodelay", true)

  if use_ssl then
    print("Connecting Blynk (secure)...")
    sock:connect(host, 443)
    local opts = {
      mode = "client",
      protocol = "tlsv1_2"
    }
    sock = assert(ssl.wrap(sock, opts))
    sock:dohandshake()
  else
    print("Connecting Blynk...")
    sock:connect(host, 80)
  end

  -- tell Blynk to use this socket
  blynk:connect(sock)
end

--[[ WiFi control ]]

blynk:on("V20", function(param)
  if param[1] == "1" then
    os.execute("wifi up")
  else
    os.execute("wifi down")
  end
end)

--[[ Locking ]]

local isLocked = true

local function advLock()
  blynk:setProperty(30,"color","#D3435C") -- red
  blynk:setProperty(30,"label","Locked")
  isLocked = true
end

local function advUnlock()
  blynk:setProperty(30,"color","#23C48E") -- green
  blynk:setProperty(30,"label","Unlocked")
  isLocked = false
end

blynk:on("V30", function(param)
  if isLocked and param[1] == "10" then
    advUnlock()
  elseif not isLocked then
    advLock()
  end
end)

--[[ Reboot ]]

blynk:on("internal:dbg", function(param)
  if param[1] == "reboot" then
    os.execute("reboot")
  end
end)

--[[ Shell ]]

blynk:on("V35", function(param)
  if isLocked then
    blynk:virtualWrite(35, "Shell is LOCKED\n")
    return
  end
  local out = exec_out(param[1])
  blynk:virtualWrite(35, out)
end)


blynk:on("disconnected", function()
  print("Disconnected.")
  -- auto-reconnect after 5 seconds
  socket.sleep(5)
  connectBlynk()
end)

--[[ Timers ]]

local prev = { spin = -1 }

local tmr1 = Timer:new{interval = 5000, func = function()
  local tx = getWanTxBytes()
  local rx = getWanRxBytes()

  if prev.tx then
    local dtx = tx - prev.tx
    if prev.dtx ~= dtx then
      blynk:virtualWrite(1, dtx / 1024 / 1024)
      prev.dtx = dtx
    end
  end
  prev.tx = tx

  if prev.rx and prev.rx ~= rx then
    local drx = rx - prev.rx
    if prev.drx ~= drx then
      blynk:virtualWrite(2, drx / 1024 / 1024)
      prev.drx = drx
    end
  end
  prev.rx = rx

  --[[
  local spin = getHddSpinning()
  if spin ~= prev.spin then
    blynk:virtualWrite(7, spin)
  end
  prev.spin = spin

  if spin then
    local rd, wt = getHddStats()

    if prev.rd then
      local drd = rd - prev.rd
      if prev.drd ~= drd then
        blynk:virtualWrite(8, drd)
        prev.drd = drd
      end
    end
    prev.rd = rd

    if prev.wt then
      local dwt = wt - prev.wt
      if prev.dwt ~= dwt then
        blynk:virtualWrite(9, dwt)
        prev.dwt = dwt
      end
    end
    prev.wt = wt
  end
  ]]

  blynk:virtualWrite(4, getActiveConnections())
  blynk:virtualWrite(5, getCpuLoad())
  blynk:virtualWrite(6, getRamUsage())
  blynk:virtualWrite(10, getArpClients())
end}

local tmr2 = Timer:new{interval = 5*60*1000, func = function()
  blynk:virtualWrite(11, string.format("%.1f", getUptime()/60/60))
end}

blynk:on("connected", function(ping)
  print("Ready. Ping: " .. math.floor(ping*1000) .. "ms")

  blynk:virtualWrite(12, getWanIP())
  blynk:virtualWrite(13, getPublicIP())
  blynk:virtualWrite(20, getWiFiStatus())
  tmr2:execute()
end)

connectBlynk()

while true do
  blynk:run()
  tmr1:run()
  tmr2:run()
end
