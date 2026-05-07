function initialize(context) {
  context.handler.useAuthMetaField("IMEI");
}

function handleRequest(context) {
  const { request, server } = context;
  let env;
  try {
    env = JSON.parse(new TextDecoder().decode(request.body));
  } catch (e) {
    return { status: 400, body: 'Invalid JSON' };
  }

  const cin = env?.['m2m:sgn']?.nev?.rep?.['m2m:cin'];
  if (!cin) return { status: 200, body: 'No m2m:cin' };

  const con = cin.con;
  if (!con || con.messageType !== 'data-received') return { status: 200, body: 'Ignored' };

  const imei = (con.ni || '').replace('urn:gsma:imei:', '');
  if (!imei) return { status: 400, body: 'No IMEI' };

  const device = server.authenticateDevice(imei);
  const decoded = hexDecode(con.data || '');
  if (!decoded) return { status: 400, body: 'Bad data' };

  let temp, lat, lon, alt, sentText;
  for (const part of decoded.split(', ')) {
    if (part.startsWith('temp: '))     temp     = Number(part.slice(6));
    else if (part.startsWith('lat='))  lat      = Number(part.slice(4));
    else if (part.startsWith('lon='))  lon      = Number(part.slice(4));
    else if (part.startsWith('alt='))  alt      = Number(part.slice(4));
    else if (part.startsWith('time=')) sentText = part.slice(5);
  }

  if (isNaN(temp) || isNaN(lat) || isNaN(lon) || !sentText) {
    return { status: 400, body: 'Missing fields' };
  }

  const sentMs = new Date(sentText.replace(' ', 'T') + 'Z').getTime();
  if (isNaN(sentMs)) return { status: 400, body: 'Bad time' };

  const now             = Math.floor(Date.now() / 1000);
  const serverReceiveMs = new Date(con.time).getTime();
  const inflight        = Math.floor((serverReceiveMs - sentMs) / 1000);

  const get = (ds) => Number(device.getDataStreamValue(ds) ?? 0);
  const set = (ds, v) => device.setDataStreamValue(ds, v);

  const count = get('MessageCount') + 1;

  const prevBytes = get('BytesReceived');
  const bytes = prevBytes + (con.data || '').length;
  if (prevBytes < 50000 && bytes >= 50000) device.logEvent('50k_bytes_used');

  const lastSentText = device.getDataStreamValue('PrevSentTime');
  const lastSentMs   = lastSentText ? new Date(lastSentText.replace(' ', 'T') + 'Z').getTime() : 0;
  const lastEpoch    = Math.floor(lastSentMs / 1000);
  let missed = get('MissedMessages');
  let sinceLastS = null;
  if (lastEpoch > 1000000000 && (now - lastEpoch) < 30 * 24 * 60 * 60) {
    sinceLastS = Math.floor((sentMs - lastSentMs) / 1000);
    const gap = Math.floor((now - lastEpoch) / (18 * 60)) - 1;
    if (gap > 0) missed += gap;
  }

  const ifMin = Math.min(get('InflightTimeMin') || inflight, inflight);
  const ifMax = Math.max(get('InflightTimeMax'), inflight);
  const ifSum = get('InflightTimeSum') + inflight;
  const ifAvg = Math.round(ifSum / count);

  const tMin = Math.min(get('TempMin') || temp, temp);
  const tMax = Math.max(get('TempMax'), temp);
  const tSum = get('TempSum') + temp;
  const tAvg = Math.round((tSum / count) * 10) / 10;

  set('Temperature',    temp);
  set('Location',       { lon, lat });
  set('Coordinates',    `${lat}, ${lon}`);
  if (!isNaN(alt)) set('Altitude', Math.round(alt));
  set('SentTime',       sentText);
  set('InflightTime',   inflight);
  set('Last Message',   decoded);

  set('MessageCount',     count);
  set('BytesReceived',    bytes);
  set('LastMessageEpoch', now);
  set('MissedMessages',   missed);
  if (sinceLastS !== null) set('TimeSinceLastMsg', sinceLastS);
  set('PrevSentTime',     sentText);

  set('InflightTimeMin', ifMin);
  set('InflightTimeMax', ifMax);
  set('InflightTimeAvg', ifAvg);
  set('InflightTimeSum', ifSum);

  set('TempMin', tMin);
  set('TempMax', tMax);
  set('TempAvg', tAvg);
  set('TempSum', tSum);

  return { status: 200, body: 'OK' };
}

function hexDecode(hex) {
  let str = '';
  for (let i = 0; i < hex.length; i += 2) {
    const b = parseInt(hex.slice(i, i + 2), 16);
    if (isNaN(b)) return null;
    str += String.fromCharCode(b);
  }
  return str;
}
