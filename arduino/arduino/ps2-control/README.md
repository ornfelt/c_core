
ino compile -b arduino:avr:nano --libraries ../libraries .

ino upload -v -b arduino:avr:nano:cpu=atmega328old -p COM7 .