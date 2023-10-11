float angle = 0;
int amplitude = 100;
int frequency = 1;

void setup() {
    Serial.begin(9600);
}

void loop() {
    float sine_value = amplitude * sin(angle);
    float cosine_value = amplitude * cos(angle);
    Serial.printf("%f %f %f\n", sine_value, cosine_value, 0);
    angle += 0.5;
}

