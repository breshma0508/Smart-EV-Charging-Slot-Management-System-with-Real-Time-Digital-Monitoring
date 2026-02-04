#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RATE_PER_HOUR 100   // ₹100 per hour
#define TOTAL_SLOTS 3       // Total parking slots (3 slots)
#define LCD_ADDRESS 0x27    // I2C LCD address (adjust if needed)

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

bool occupiedSlots[TOTAL_SLOTS] = {false};  // Slot status (free or occupied)
unsigned long slotEndTime[TOTAL_SLOTS] = {0};  // Time when slots get freed

void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("WELCOME");
    delay(2000);  // Show the initial message for 2 seconds
    lcd.clear();
    lcd.print("EV-station");
    delay(2000);  // Show the initial message for 2 seconds
    lcd.clear();
    lcd.print("Scan QR to Pay");
    Serial.println("Setup Complete");
    Serial.println("Enter amount, sir or madam");
}

void loop() {
    checkExpiredSlots(); // Check if any slot has expired and free it

    if (Serial.available()) {
        int amount = Serial.parseInt();  // Read payment amount
        while (Serial.available()) Serial.read(); // Clear buffer

        if (amount >= 100 && amount <= 600) {
            int allocatedTime = 0;

            // Allocate time based on the amount
            if (amount >= 100 && amount <= 200) {
                allocatedTime = 4; // 4 hours for ₹100 to ₹200
            } else if (amount > 200 && amount <= 600) {
                allocatedTime = 5; // 5 hours for ₹201 to ₹600
            }

            int slot = findAvailableSlot(); // Find first free slot

            if (slot != -1) { // If a free slot is available
                occupiedSlots[slot] = true; // Mark slot as occupied
                slotEndTime[slot] = millis() + (allocatedTime * 3600000UL); // Store slot expiration time

                // Display allocated slot and time
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Slot: ");
                lcd.print(slot + 1);  // Display slot number on LCD

                lcd.setCursor(0, 1);
                lcd.print("Time: ");
                lcd.print(allocatedTime);
                lcd.print(" Hr");

                Serial.print("Amount Entered: "); Serial.println(amount);
                Serial.print("Allocated Slot: "); Serial.println(slot + 1);
                Serial.print("Slot:"); Serial.print(slot + 1);
                Serial.print(" Time:"); Serial.print(allocatedTime); Serial.println(" Hr");

                delay(5000);  // Wait for 5 seconds before displaying the next information
            } else {
                // If no slot is available, show the "No available slots!" message
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("No slots free!");
                Serial.println("No available slots!");
                delay(5000);  // Wait for 5 seconds before displaying again
            }
        } else {
            // If payment is less than ₹100 or greater than ₹600, show this message
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Amount must be ₹100-₹600!");
            Serial.println("Amount:₹100-₹600!");
            delay(5000);  // Wait for 5 seconds before displaying again
        }
    }

    // Display remaining time for each occupied slot
    displayRemainingTime();
}

// Function to find the first available slot
int findAvailableSlot() {
    for (int i = 0; i < TOTAL_SLOTS; i++) {
        if (!occupiedSlots[i]) return i; // Return first free slot
    }
    return -1; // No slots available
}

// Function to check if any slot has expired and free it
void checkExpiredSlots() {
    unsigned long currentTime = millis();
    for (int i = 0; i < TOTAL_SLOTS; i++) {
        if (occupiedSlots[i] && currentTime >= slotEndTime[i]) {
            occupiedSlots[i] = false; // Free the slot
            Serial.print("Slot ");
            Serial.print(i + 1);
            Serial.println(" is now free.");
        }
    }
}

// Function to display the remaining time for each occupied slot
void displayRemainingTime() {
    unsigned long currentTime = millis();

    for (int i = 0; i < TOTAL_SLOTS; i++) {
        if (occupiedSlots[i]) {
            // Calculate remaining time for this slot
            unsigned long remainingTime = slotEndTime[i] - currentTime;
            if (remainingTime > 0) {
                unsigned long remainingHours = remainingTime / 3600000UL;  // Convert milliseconds to hours
                unsigned long remainingMinutes = (remainingTime % 3600000UL) / 60000; // Convert remainder to minutes

                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Slot: ");
                lcd.print(i + 1);
                lcd.setCursor(0, 1);
                lcd.print("Time:");
                lcd.print(remainingHours);
                lcd.print(" Hr ");
                lcd.print(remainingMinutes);
                lcd.print(" Min");

                Serial.print("Slot: ");
                Serial.print(i + 1);
                Serial.print("Time: ");
                Serial.print(remainingHours);
                Serial.print(" Hr ");
                Serial.print(remainingMinutes);
                Serial.println(" Min");

                delay(5000);  // Wait for 5 seconds before displaying next slot's remaining time
            }
        }
    }
}