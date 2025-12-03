🔐 Password Manager – C Console Application

A lightweight command-line password manager written in C that securely stores credentials in an encrypted binary file. All usernames and passwords are XOR-encrypted before saving to disk. Works fully offline.

🚀 Features

Master Authentication: Secure access with a master password (1234 by default).

Manage Credentials: Add website login credentials easily.

Search & View: Search stored credentials or view the entire list.

Persistent Storage: Data is saved to passwords.dat (encrypted).

Local & Fast: Runs entirely on your machine without internet dependencies.

📂 Project Structure

PasswordManager/
├── src/
│   └── PasswordManager.c    # Main source code
├── data/
│   └── passwords.dat        # Auto-generated encrypted data (not stored in Git)
└── README.md                # Project documentation


🛠️ Build & Run

Linux / macOS

# Compile the program
gcc src/PasswordManager.c -o passwordmgr

# Run the application
./passwordmgr


Windows (MinGW)

:: Compile the program
gcc src/PasswordManager.c -o passwordmgr.exe

:: Run the application
passwordmgr.exe


🧩 Usage

Launch the program using the commands above.

Enter the master password:

1234


Choose an action from the menu:

1 → Add new credential

2 → View or search saved credentials

3 → Exit

Credentials are automatically encrypted and saved into passwords.dat upon entry.

🔏 Encryption Information

This project uses XOR-based reversible encryption for demonstration purposes.

Encryption Key: 'X'

Status:

✔ Good for learning C file handling and basic bitwise operations.

⚠ Not suitable for real-world high-security password storage.

📌 Planned Improvements

[ ] Stronger encryption (Hashed master password, AES implementation)

[ ] Better input protection (Masking password characters with *)

[ ] Edit and Delete functionality for specific credentials

[ ] Backup and Export support (CSV/JSON)

[ ] Enhanced input validation and UI improvements

👤 Author

Aditya Dewangan
