//SPI Pins for RF24
#define CE 8
#define CNS 10

const byte address[] = "00001";

RecieveData data;

RF24 *rf24 = new RF24(CE,CNS);

void startCommunication() {
    rf24->begin();
    rf24->openReadingPipe(0, address);
    rf24->setPALevel(RF24_PA_MAX);
    rf24->setDataRate(RF24_250KBPS);
    rf24->startListening();
}

RecieveData getData() {
    rf24->read(&data, sizeof(RecieveData));
    return data;
}

bool isAvailable() {
    return rf24->available();
}
