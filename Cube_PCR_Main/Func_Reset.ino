void AutoReset() {
  pinMode(AutoResetPin, OUTPUT);
  digitalWrite(AutoResetPin, LOW);
}
