#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgcodecs.hpp>

#include "face_detect.hpp"
#include "config.hpp"

#include <Keypad.h>


#define Password_Lenght 5
#define PIEZO    8
#define RELAY    A0

#include <LiquidCrystal_I2C.h>

#include <iostream>
#include <stdio.h>
#include <tgbot/tgbot.h>
#include<wiringPi.h> // alike GPIO

#define TOKEN "1407581882:AAHl3q7nJ97I7eql6Gic0t76rde6gwlhlGs"
#define chat_ID 824356636

LiquidCrystal_I2C lcd(0x27, 20, 2);


int pos = 0;    // variable to store the servo position

char Data[Password_Lenght]; 
char Master[Password_Lenght] = "5698";
byte data_count = 0, master_count = 0;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char keys [ROWS] [COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {6, 5, 4, 3};
byte colPins[COLS] = {11, 10, 9, 7};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char inChar;
String inString;

std::string get_model_name(int argc, char *argv[]) {

    std::string model_name;
    if (argc != 2) {
        std::cout << "Error: Correct usage: ./train <model_name>" << std::endl;
        exit(1);
    } else {
        return argv[1];
    }

}

void setup() {
  pinMode(PIEZO, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print(" ENTER PASSWORD");
}

void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count–] = 0; //clear array for new data
  }
  return;
}


int main(int argc, char *argv[]) {

    TgBot::Bot bot(TOKEN);
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Ola! Informaremos se algum desconhecido tentar abrir seu cofre!");
    });

    bot.getEvents().onCommand("urso", [&bot](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(medelay
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
            }
        } catch (TgBot::TgException& e) {
            printf("error: %s\n", e.what());
        }

	GPIO input_pin("17", "in");
	std::cout << input_pin.read_value() << std::endl;

	std::string model_name = get_model_name(argc, argv);

	std::cout << "Loading model..." << std::flush;
	cv::Ptr<cv::face::FaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
	model->read(std::string(MODEL_DIR) + model_name + ".xml");
	std::cout << "[DONE]" << std::endl;

	cv::VideoCapture camera = get_camera();

	bool loop = true;
	while (loop) {

		cv::Mat image;

		flush_capture_buffer(camera);
		camera >> image;
		cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);

		std::vector<cv::Rect> face_regions = detect_faces(image);
		std::cout << "Deteced " << face_regions.size() << " faces." << std::endl;

    lcd.printf(" Waiting recognition...");

		if (face_regions.size() == 1) {

			image = image(face_regions[0]);
			cv::resize(image, image, cv::Size(FACE_WIDTH, FACE_HEIGHT), 0, 0, cv::INTER_LANCZOS4);

			int label;
			double confidence;
			model->predict(image, label, confidence);

			std::cout << "Results: " << label << ", " << confidence << std::endl;

			// If a face is recognized and authorized
			if (label != 0 && confidence <= POSITIVE_THRESHOLD) {
				std::cout << "******   Detected allowed face with label: " << label << std::endl;
				  customKey = myKeypad.getKey();
                if (customKey)                 
                {
                    Data[data_count] = customKey; 
                    data_count++;                 
                }

                if (data_count == Password_Lenght – 1) 
                    if (!strcmp(Data, Master))           
                    {
                    digitalWrite(RELAY, LOW);
                    lcd.clear();
                    lcd.print("    DOOR OPEN");
                    sleep(5000);                      
                    lcd.clear();
                    lcd.print("    DOOR LOCK");
                    digitalWrite(RELAY, HIGH);
                    sleep(1000);
                    lcd.clear();
                    lcd.printf(" Waiting recognition...");
                    {
                else {
                  bot.getApi().sendMessage(chat_ID, "Intruso");
                  lcd.clear();
                  lcd.print(" WRONG PASSWORD");
                  }
                  clearData();
                  } 
          }
            } 

		std::string input;
		std::cout << "Enter 'q' to quit, or any other key to take another picture: " << std::endl;
		std::cin >> input;
		if (input == "q" || input == "Q") {
			loop = false;
		}

	}

}