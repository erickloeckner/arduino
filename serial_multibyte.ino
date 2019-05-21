// read multi-byte serial data. format is example is 2 int8_t vars and 2 int32_t vars
// python command to send data: serial.Serial.write(struct.pack('<bbii', 1, 1, 1, 1))

const uint8_t BUF_SIZE = 10;
uint8_t buf[BUF_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t buf_i = 0;
uint8_t ser_in = 0;

int8_t cmd_1 = 0;
int8_t cmd_2 = 0;
int32_t point_x = 0;
int32_t point_y = 0;

int8_t in_byte = 0;

void setup() {
    Serial.begin(112500);
    while (!Serial) {
        ;
    }
    
}

void loop() {
    while (Serial.available()) {
        in_byte = Serial.read();
        
        if (!ser_in) {
            ser_in = 1;
        }
        
        if (buf_i < BUF_SIZE) {
            buf[buf_i] = in_byte;
            buf_i++;
        }
    }
    
    if (ser_in) {
        cmd_1 = buf[0];
        cmd_2 = buf[1];
        
        point_x = buf[2] | buf[3] << 8 | buf[4] << 16 | buf[5] << 24;
        point_y = buf[6] | buf[7] << 8 | buf[8] << 16 | buf[9] << 24;
        
        Serial.print("cmd1: ");
        Serial.print(cmd_1);
        Serial.print(" ");
        
        Serial.print("cmd2: ");
        Serial.print(cmd_2);
        Serial.print(" ");
        
        Serial.print("X: ");
        Serial.print(point_x);
        Serial.print(" ");
        
        Serial.print("Y: ");
        Serial.print(point_y);
        Serial.print(" ");
        
        //~ for (int i = 0; i < BUF_SIZE; i++) {
            //~ Serial.print(buf[i]);
            //~ Serial.print(' ');
        //~ }
        ser_in = 0;
        
        buf_i = 0;
    }
}
