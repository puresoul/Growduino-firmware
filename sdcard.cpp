#include "GrowduinoFirmware.h"

#include <SD.h>
#include <aJSON.h>

const int chipSelect = 4;

void sdcard_init(){
    pinMode(53, OUTPUT);
    SD.begin(chipSelect);
}

bool file_exists(const char * dirname) {
    // check if directory (or full filename) exists
    return file_exists(dirname, NULL);
}

bool file_exists(const char * dirname, const char * filename) {
    char full_file_name[70];
    strlcpy(full_file_name, dirname, 55);
    if (filename == NULL) {
        return SD.exists(full_file_name);
    } else {
        if (strlen(dirname) > 50) {
            //we dont do that deep dirs
            return false;
        }
        strlcpy(full_file_name, dirname, 55);
        strlcat(full_file_name, "/", 70);
        strlcat(full_file_name, filename, 70);
        return SD.exists(full_file_name);

    }
}

void file_passthru(const char * dirname, const char * filename, Stream * input) {
    char filepath[128];
    if (strlen(dirname) > 50) {
        //we dont do that deep dirs
        return;
    }
    strlcpy(filepath, dirname, 55);
    if (!file_exists(filepath) && dirname[0] == '/') {
#ifdef DEBUG_SDCARD
        Serial.print(F("Creating directory: "));
#endif
        SD.mkdir(filepath);
    }
    strlcat(filepath, "/", 60);
    strlcat(filepath, filename, 60);

    Serial.print(F("Writing file "));
    Serial.println(filepath);

    if (file_exists(filepath)) {
        SD.remove(filepath);
    }

    digitalWrite(13, 1);

#ifdef DEBUG_SDCARD
    Serial.print(F("."));
#endif

    File dataFile = SD.open(filepath, FILE_WRITE);
#ifdef DEBUG_SDCARD
    Serial.print(F("."));
#endif
    if (dataFile) {
        Serial.print(F("saving data to disk"));
        int remain = 0;
        while ((remain = input->available())) {
            remain = min(remain, 127);
            for (int i=0; i < remain; i++) {
                filepath[i] = (char) input->read();
            }
            filepath[remain] = 0;
            dataFile.write(filepath);
            Serial.print(F("."));
        };
        dataFile.close();

    } else {
        Serial.print(F("Failed to open "));
        Serial.println(filepath);
    }
#ifdef DEBUG_SDCARD
    Serial.println(F("."));
#endif
    digitalWrite(13, 0);
}

void file_write(const char * dirname, const char * filename, aJsonObject * data) {
    char filepath[60];
    if (strlen(dirname) > 50) {
        //we dont do that deep dirs
        return;
    }
    strlcpy(filepath, dirname, 55);
    if (!file_exists(filepath) && dirname[0] == '/') {
#ifdef DEBUG_SDCARD
        Serial.print(F("Creating directory: "));
#endif
        SD.mkdir(filepath);
    }
    strlcat(filepath, "/", 60);
    strlcat(filepath, filename, 60);

    Serial.print(F("Writing file "));
    Serial.println(filepath);

    if (file_exists(filepath)) {
        SD.remove(filepath);
    }

    digitalWrite(13, 1);

#ifdef DEBUG_SDCARD
    Serial.print(F("."));
#endif

    File dataFile = SD.open(filepath, FILE_WRITE);
#ifdef DEBUG_SDCARD
    Serial.print(F("."));
#endif
    if (dataFile) {
        aJsonStream sd_stream(&dataFile);
        aJson.print(data, &sd_stream);
#ifdef DEBUG_SDCARD
        Serial.print(F("."));
#endif
        dataFile.close();
#ifdef DEBUG_SDCARD
        Serial.print(F("."));
#endif
    } else {
        Serial.print(F("Failed to open "));
        Serial.println(filepath);
    }
#ifdef DEBUG_SDCARD
    Serial.println(F("."));
#endif
    digitalWrite(13, 0);
}

aJsonObject * file_read(const char * dirname, const char * filename){
    char filepath[60];

    if (strlen(dirname) > 50 || strstr(dirname, "..") != NULL) {
        //we dont do that deep dirs, we dont support taversal up
        return NULL;
    }

    strcpy(filepath, dirname);
    strncat(filepath, "/", sizeof(filepath) - 2);
    strncat(filepath, filename, sizeof(filepath) - strlen(filename) - 1);
    //strcat(filepath, "/");
    //strcat(filepath, filename);

    Serial.print(F("opening file "));
    Serial.println(filepath);

    if (!SD.exists(filepath)) {
        Serial.println(F("File does not exist"));
        return NULL;
    }
    File dataFile = SD.open(filepath, FILE_READ);
    if (dataFile) {
        aJsonStream sd_stream(&dataFile);
        aJsonObject * data = aJson.parse(&sd_stream);
        dataFile.close();
        return data;
    } else {
        Serial.println(F("File read failure"));
        return NULL;
    }

}
