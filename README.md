# RFID-Based Smart Cart with Anti-Theft System

## 📖 Overview

RFID-Based Smart Cart is an ARM7 LPC2129-based embedded system that automates supermarket billing and prevents theft using RFID technology.

The system allows customers to add or remove products from a shopping cart using RFID tags. The total bill is calculated automatically and displayed on an LCD. Before exiting the store, the customer must complete payment using an authorized RFID payment card. An anti-theft mechanism verifies payment status and controls gate access.

This project demonstrates RFID interfacing, UART communication, LCD interfacing, interrupt handling, and embedded system design using Embedded C.

---

## 🎯 Features

- RFID-based product identification
- Automatic billing system
- Product addition and removal
- Real-time bill calculation
- RFID-based payment verification
- Anti-theft security mechanism
- LCD display interface
- Buzzer alert system
- LPC2129 ARM7 microcontroller implementation

---

## 🛠 Hardware Requirements

- LPC2129 ARM7 Microcontroller
- RFID Reader Module (EM-18 -passive tags)
- RFID Tags
- 20x4 Alphanumeric LCD Display
- Push Buttons
- Buzzer
- Power Supply Circuit

---

## 💻 Software Requirements

- Embedded C
- Keil uVision
- Flash Magic
- Proteus (Optional)

---

## ⚙ System Working

### Product Addition Mode

1. Press Add Product button.
2. Scan product RFID tag.
3. Product information is displayed.
4. Product price is added to the bill.
5. Quantity is updated automatically.

### Product Removal Mode

1. Press Remove Product button.
2. Scan product RFID tag.
3. Product quantity is reduced.
4. Product price is deducted from the bill.

### Billing Mode

1. Press Bill button.
2. Complete product list is displayed.
3. Total bill amount is calculated.
4. System waits for payment card authentication.

### Payment Verification

1. Scan authorized payment RFID card.
2. Payment status becomes successful.
3. User is allowed to proceed to exit verification.

### Gate Verification

1. Scan gate RFID card.
2. If payment is completed:
   - Gate access is granted.
3. If payment is not completed:
   - Theft alert is activated.

---

## 🔒 Anti-Theft Mechanism

The system continuously monitors payment status.

### If customer exits without payment:

- Theft alert displayed
- Buzzer activated
- Exit denied

### If unauthorized RFID card is used:open gate

- Theft alert displayed
- Buzzer activated
- Exit denied

### If payment is successful:

- Gate access granted
- Customer can leave the store

---

## 📦 Product Database

| Product   | Price (₹) |
|-----------|-----------|
| SOAP      |    35     |
| MILK      |    60     |
| BISCUIT   |    20     |
| CHOCOLATE |    40     |

RFID tags are mapped to product information within the firmware.

---

## 📟 LCD Display Information

The LCD displays:

- Product Name
- Product Price
- Product Quantity
- Total Bill
- Payment Status
- Gate Status
- Theft Alerts

---

## 🔄 System Flow

```text
START
   |
   V
Scan Product RFID
   |
   V
Add / Remove Product
   |
   V
Update Bill
   |  
   V
Generate Final Bill
   |
   V
Scan Payment RFID
   |
   +----No----> Payment Pending
   |
  Yes
   |
   V
Scan Gate RFID
   |
   +----Invalid----> Theft Alert
   |
 Valid
   |
   V
Gate Opened
   |
   V
END
```

## 📂 Project Structure

```text
RFID-BASED-SMARTCART/
│
├── trollyfinal.c
├── UART0header.h
├── lcdheader.h
├── delayheader.h
├── title.h
└── README.md
```

### File Description

| File          | Description                  |
|---------------|------------------------------|
| trollyfinal.c | Main application source code |
| UART0header.h | UART driver functions        |
| lcdheader.h   | LCD interface functions      |
| delayheader.h | Delay utility functions      |
| title.h       | Startup display screen       |

---

## 🔧 LPC2129 Peripherals Used

| Peripheral | Purpose |
|------------|---------|
| UART0 | RFID Reader Communication |
| GPIO | Switches and Buzzer |
| Timer | Delay Generation |
| Interrupts | RFID Data Reception |
| LCD Interface | User Display |

---

## 🚀 Applications

- Smart Shopping Trolleys
- Supermarkets
- Retail Stores
- Automated Billing Systems
- RFID-Based Inventory Systems
- Smart Retail Automation

---

## 🎓 Learning Outcomes

This project demonstrates:

- ARM7 LPC2129 Programming
- Embedded C Development
- UART Communication
- RFID Technology
- LCD Interfacing
- Interrupt Programming
- Billing Automation
- Security System Design

---

## 🔮 Future Enhancements

- GSM Bill Notification
- Mobile Application Integration
- QR Code Payment
- IoT-Based Monitoring
- Cloud Database Support
- Inventory Management System
- Online Payment Gateway

---

## ✅ Project Outcome

- Successful RFID product identification
- Automatic bill generation
- Product addition and removal support
- RFID payment verification
- Anti-theft protection
- Reduced billing time
- Improved customer shopping experience

---

## 👨‍💻 Author

**Chinnadurai V**

Embedded Systems Developer

GitHub:
https://github.com/chinna-30/RFID-BASED-SMARTCART

---


This project is developed for educat
