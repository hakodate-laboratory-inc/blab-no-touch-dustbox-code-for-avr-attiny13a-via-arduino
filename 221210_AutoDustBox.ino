//"221210_No Touch DustBox Servo Motor And Photo Reflector For Attiny13a" from @deckeye
//Arduino から、”Arduino as ASP（MicroCore）” を使って、ATtiny13a に書き込みをして、サーボモーターを動かすプログラムです。
//詳細などは、底部に書いておきます。

#define PB2 3 //2番ピン
#define PB0 0 //5番ピン

unsigned int ServoHighMicroSec = 600; //500-2400μs。サーボモーターに流すパルス長。
unsigned int ServoStatus = 600; //500-2400μs。サーボモーターに流すパルス長。

void setup() {
  pinMode(PB2, OUTPUT);
  pinMode(PB0, INPUT);
}

void servo(){
  //しばらく同じ長さのパルスを出し続けるコードです
  for(int i=0; i<80; i++){
     
     if     (ServoStatus<ServoHighMicroSec)ServoStatus=ServoStatus+25;
     else if(ServoStatus>ServoHighMicroSec)ServoStatus=ServoStatus-25;
     
    //しばらく(40ループ分)同じパルスを出し続ける。
    //パルスを出している間しか動いてくれない(10カウントだと回転途中で終わる)
    //ので、気持ち長めの30カウント()にしました。
    digitalWrite(PB2, HIGH);
    delayMicroseconds(ServoStatus);
    digitalWrite(PB2, LOW);
    delayMicroseconds(8000); //仕様上20000μsまでは入れられない(16383μs以内)ので、10000μsに分割。
    delayMicroseconds(10000-ServoStatus); //周期長から、HIGHの時間分引いている感じですね。
  } 
}

void loop() {
  
  //PhotoReflectorInput = anatogRead(PB0); //0-1023。フォトリフレクタから流れてくる電圧(赤外線LEDから何かを反射して帰ってきた光の強さ。外光の赤外線も拾うので注意)。
  while(!digitalRead(PB0));
  ServoHighMicroSec = 800;
  servo();
  
  while(digitalRead(PB0));
  delay(1000);
  ServoHighMicroSec = 1750;
  servo();
}




//設定項目など詳細情報
//Arduino IDE Ver.1.8.13 で動作確認済み。2022年12月時点では、MocroCoreがIDEVer.2系には対応してないみたいです(エラーが出る。異論は募集中。)
//他の記事を参考にしながら、MicroCoreのATtiney13aを動かす記事を見て、設定してみてください。
//周波数は"9.6MHz internal osc."でやってます。
//タイミングは"micros enablaed"でやってます。
//動作確認時は、ATtiney13a の電源は、Arduinoではなく、別電源からの供給にしてください(でないと電流不足で再起動＋信号電流不足してるっぽいです)
//本当はサーボ周りのライブラリを使いたかったのですが、どうにも上手く扱えなかったので、digitalWrite()とdelayMicroseconds()のゴリ押しPWMでやっています。
//この辺のゴリ押し具合は、IchigoJam で身に付けたのかもしれません。
//ともあれ、この辺で。 deckeye こと中村拓也でした。
