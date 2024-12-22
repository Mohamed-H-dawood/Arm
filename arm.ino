#include <Servo.h>

// تعريف السيرفو
Servo myServos[5];

// تعريف مداخل أجهزة الفليكس سينسور
const int flexPins[5] = {A0, A1, A2, A3, A4}; // مداخل الفليكس سينسور
int flexValues[5];    // قراءة القيم من أجهزة الفليكس
int angles[5];        // زوايا السيرفو

void setup() 
{
  // توصيل السيرفو بالمخارج الرقمية
  myServos[0].attach(9);
  myServos[1].attach(10);
  myServos[2].attach(11);
  myServos[3].attach(12);
  myServos[4].attach(13);

  Serial.begin(9600); // إعداد المراقب التسلسلي
}

void loop()
{
  bool multipleSensors = false; // لمعرفة إذا تحرك أكثر من حساس

  for (int i = 0; i < 5; i++) {
    flexValues[i] = analogRead(flexPins[i]); // قراءة قيمة الفليكس
    angles[i] = map(flexValues[i], 750, 900, 0, 180); // تحويل القيم إلى زاوية (0-180)
    angles[i] = constrain(angles[i], 0, 180); // التأكد من بقاء الزاوية ضمن النطاق

    // التحقق من تحرك أكثر من حساس
    if (flexValues[i] > 750) { // قم بتعديل هذه القيمة حسب الحساسات لديك
      multipleSensors = true;
    }
  }

  if (multipleSensors) {
    // إذا تحرك أكثر من حساس، قم بمزامنة الحركات
    for (int i = 0; i < 5; i++) {
      if (flexValues[i] > 750) { // قم بتحريك السيرفو فقط إذا كانت القيم كبيرة
        myServos[i].write(angles[i]); // تحريك السيرفو
      }
    }
  } else {
    // تحريك السيرفو لكل حساس على حدة
    for (int i = 0; i < 5; i++) {
      myServos[i].write(angles[i]); // تحريك السيرفو
    }
  }

  // عرض القيم على المراقب التسلسلي
  for (int i = 0; i < 5; i++) {
    Serial.print("Flex Sensor ");
    Serial.print(i + 1);
    Serial.print(" Value: ");
    Serial.print(flexValues[i]);
    Serial.print(" | Angle: ");
    Serial.println(angles[i]);
  }

  delay(15); // تأخير قصير لتحسين الأداء
}
