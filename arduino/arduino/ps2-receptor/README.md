
ino compile -b arduino:avr:uno --libraries ../libraries .
ino upload -v -b arduino:avr:uno:cpu=atmega328old -p COM7 .