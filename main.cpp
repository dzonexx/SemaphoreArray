

#include "glob.hpp"
#include "UART.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <list>
using namespace std;

#define BAUDRATE 115200
#define UART_DEV_PATTERN "/dev/ttyUSB*"

int main() {
	vector<string> usb_devs = glob(UART_DEV_PATTERN);
	cout << "INFO: USB_Logger: usb_devs:" << endl;
	for(const auto usb_dev: usb_devs){
		cout << "\t" << usb_dev << endl;
	}	

	vector<shared_ptr<UART>> serials;
	for(auto usb_dev: usb_devs){
		auto s = new UART(
			usb_dev,
			BAUDRATE
		);
		serials.emplace_back(s);
	}
	if(serials.empty()){
		cout << "WARN: USB_Logger: No any USB UART dev plugged in!" << endl;
		return 0;
	}
	
	shared_ptr<UART> serial = serials[serials.size()-1];
	cout << "Enter which LED should be switched on" << endl;
	char led[4];
	cin >> led;
	serial->write(led);
	while(true){
		uint8_t x;
		serial->read(x);
		if(x == 1){
			cout << "Prvi switch je pritisnut" << endl;
			serial->write("DESNO");
		}else if(x == 2){
			cout << "Drugi switch je pritisnut" << endl;
			serial->write("LEVO");
		}else if(x == 4){
			cout << "Treci switch je pritisnut" << endl;
			serial->write("DESNO");
		}else if(x == 8){
			cout << "Cetvrti switch je pritisnut" << endl;
			serial->write("LEVO");
		}else if(x == 16){
			cout << "Peti switch je pritisnut" << endl;
			serial->write("DESNO");
		}else if(x == 32){
			cout << "Sesti switch je pritisnut" << endl;
			serial->write("LEVO");
		}
	}
	
	return 0;
}
