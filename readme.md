# M5_Sensor_Ambient   
Ambientで可視化をする   
参考: https://ambidata.io/samples/m5stack/m5stack_pulse_gps/   
   
## スクリーンショット
<img src="https://github.com/tanopanta/image/blob/master/kenkyu/amb.png" width="420px">
   
## 機能   
(現在のところ)   
1分毎に
- 心拍数
- 覚醒度または眠気
- 快不快
- 歩数
- 緯度経度   

を送信しグラフ化
## 使い方   
1. Ambientのアカウントを作りチャンネル作成   
[Ambientを使ってみる](https://ambidata.io/docs/gettingstarted/)   
1. このリポジトリをクローンまたはDownload ZIP   
1. template_myconfig.h.txt を開きパラメータを設定し myconfig.h にリネーム   
1. ライブラリを追加   
[GitHubにある ZIP形式ライブラリ のインストール方法 ( Arduino IDE )](https://www.mgo-tec.com/arduino-ide-lib-zip-install)
    - Ambient.h   
    https://github.com/AmbientDataInc/Ambient_ESP8266_lib
    - PulseSensorPlayground.h   
    心拍数用ライブラリ
    https://github.com/tanopanta/MyPulseSensorPlayground  
    - SparkFunMPU9250-DMP.h   
    歩数計用ライブラリ   
    https://github.com/sparkfun/SparkFun_MPU-9250-DMP_Arduino_Library   
    - Wi-Fi位置情報(wifiToGeo.h, wifiToGeo.cpp)   
    https://github.com/tanopanta/M5Stack_WiFi_Geolocation
1. ArduinoIDEでコンパイルし実行   