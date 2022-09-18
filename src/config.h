/**
 * GIPOとADCのピン(チャンネル)に関する設定
 * 種類_OF_機能 チャンネルorピン
 */
#define IO_PIN_OF_DRIVE 27
#define IO_PIN_OF_SPEED 2
#define ADC_CH_OF_THROTTLE 0
#define ADC_CH_OF_CURRENT 1
#define ADC_CH_OF_VOLTAGE 2
#define ADC_CH_OF_DRIVE_TEMP 3
#define ADC_CH_OF_MOTOR_TEMP 4

/**
 * モータドライブに関する設定
 */
//ESP32のPWMチャンネル
#define DRIVE_PWM_CH 0
//PWMのキャリア周波数
#define DRIVE_PWM_FREQ 10000
//PWM duty比のbit数
#define DRIVE_PWM_RESO 12
//最大電流[mA]
#define DRIVE_CURRENT_LIMIT 13000
//出力停止する最大電流超過割合(リニア)[%]
#define DRIVE_CURRENT_LIMIT_OVER 50
//PWM Duty比が0%から100%まで変化する最短時間
#define DRIVE_0to100_TIME 1000

/**
 * 運行に関する設定
 */
//速度制限
#define SPEED_LIMIT 20
//磁石数
#define MAGNET_COUNT 4
//磁石間の長さ
#define MAGNET_INTERVAL 260

/**
 * 表示に関する設定
 */
//表示FPS
#define DISPLAY_LOOP_INTERVAL 500
