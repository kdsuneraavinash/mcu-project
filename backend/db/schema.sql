DROP TABLE IF EXISTS entry;

CREATE TABLE entry (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  identifier TEXT UNIQUE NOT NULL,
  sender TEXT NOT NULL,
  sent TIMESTAMP NOT NULL,
  status TEXT NOT NULL,
  msgType TEXT NOT NULL,
  scope TEXT NOT NULL,
  info_category TEXT NOT NULL,
  info_event TEXT NOT NULL,
  info_responseType TEXT NOT NULL,
  info_urgency TEXT NOT NULL,
  info_severity TEXT NOT NULL,
  info_certainty TEXT NOT NULL,
  info_senderName TEXT NOT NULL,
  info_parameter_temp_mean NUMERIC NOT NULL,
  info_parameter_temp_std NUMERIC NOT NULL,
  info_parameter_humidity_mean NUMERIC NOT NULL,
  info_parameter_humidity_std NUMERIC NOT NULL,
  info_parameter_pressure_mean NUMERIC NOT NULL,
  info_parameter_pressure_std NUMERIC NOT NULL,
  info_parameter_light_mean NUMERIC NOT NULL,
  info_parameter_light_std NUMERIC NOT NULL
);

