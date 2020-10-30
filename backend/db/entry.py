from db.database import get_db
from datetime import datetime


def get_all_entries():
    c = get_db().cursor()
    c.execute("""
    select identifier, CAST(sent as TEXT) as sent,
               info_parameter_temp_mean, info_parameter_temp_std, 
               info_parameter_humidity_mean, info_parameter_humidity_std,
               info_parameter_pressure_mean, info_parameter_pressure_std, 
               info_parameter_light_mean, info_parameter_light_std 
    from entry order by sent;
    """)
    return c.fetchall()


def save_entry(cap, params):
    conn = get_db()
    c = conn.cursor()
    c.execute("""
        INSERT INTO entry (identifier, sender, sent, status, msgType, scope, 
                       info_category, info_event, info_responseType,
                       info_urgency, info_severity, info_certainty, info_senderName, 
                       info_parameter_temp_mean,  info_parameter_temp_std, 
                       info_parameter_humidity_mean, info_parameter_humidity_std,
                       info_parameter_pressure_mean, info_parameter_pressure_std, 
                       info_parameter_light_mean, info_parameter_light_std)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    """,
              (
                  str(cap['cap_id']),
                  str(cap['cap_sender']),
                  datetime.fromisoformat(str(cap['cap_sent'])),
                  str(cap['cap_status']),
                  str(cap['cap_message_type']),
                  str(cap['cap_scope']),
                  str(cap['cap_info'][0]['cap_category']),
                  str(cap['cap_info'][0]['cap_event']),
                  str(cap['cap_info'][0]['cap_response_type']),
                  str(cap['cap_info'][0]['cap_urgency']),
                  str(cap['cap_info'][0]['cap_severity']),
                  str(cap['cap_info'][0]['cap_certainty']),
                  str(cap['cap_info'][0]['cap_sender_name']),
                  float(params['TEMP_MEAN']),
                  float(params['TEMP_STD']),
                  float(params['HUMIDITY_MEAN']),
                  float(params['HUMIDITY_STD']),
                  float(params['PRESSURE_MEAN']),
                  float(params['PRESSURE_STD']),
                  float(params['LIGHT_MEAN']),
                  float(params['LIGHT_STD']),
              ))
    conn.commit()
