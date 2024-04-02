ino compile -b arduino:avr:nano --libraries ../libraries .
ino upload -v -b arduino:avr:nano:cpu=atmega168 -p COM7 .