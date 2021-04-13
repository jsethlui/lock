
#!/usr/bin/env python3

import getopt       # short command line args
import sys          # args
import os           # file existance
import getpass      # password input
import signal       # kill and terminate signals
import hashlib      # hashing
import time         # sleeping
import random       # random numbers

class Color:
    FAIL    = '\033[91m'    # red
    SUCCESS = '\033[92m'    # green
    BOLD    = '\033[1m'     # bold
    END     = '\033[0m'     # end

def signalHandler(sig, frame):
    print("\nExiting...\n")
    sys.exit(0)

def main(argv):
    '''
    r) read        read from passwords vault
    w) write       write data to vault
    g) generate    generate password + write to password to vault
    s) sudo        manually edit vault
    '''

    readFlag = False
    writeFlag = False 
    generateFlag = False
    sudoFlag = False

    signal.signal(signal.SIGINT, signalHandler)

    try:
        opts, args = getopt.getopt(argv, "rwgs", [])
    except getopt.GetoptError:
        sys.stderr.write(Color.FAIL + "Correct Usage: " + Color.END + "genpass.py -r -w -g -s\n")
        sys.exit(2)
    for opt, arg in opts:
        if (opt == "-r"):                       # read
            readFlag = True
        elif (opt == "-w"):                     # write
            writeFlag = True
        elif (opt == "-g"):                     # generate
            generateFlag = True
        elif (opt == "-s"):
            sudoFlag = True
            textEditor = arg

    if (os.path.exists("vault.txt") == False):  # if file that stores passwords does not exist
        sys.stderr.write(Color.FAIL + "Error: " + Color.END + "vault does not exist. Please use installer\n")
        sys.exit(1)

    os.chmod("vault.txt", 0o777)                # make vault.txt readable, writable, and executable         

    if (len(sys.argv) == 1):
        sys.stderr.write(Color.FAIL + "Error: " + Color.END + "must specify argument [rwgs]\n")
        sys.exit(1)     

    # read all passwords
    if (readFlag == True):
        f = open("vault.txt", "r")                 
        print(Color.BOLD + "Reading from Vault" + Color.END)
        allLines = f.readlines()
        for string in allLines:
            print(string.strip())
        f.close()

    # write password to vault
    if (writeFlag == True):
        f = open("vault.txt", "a")                 
        f.write("\n")
        print(Color.BOLD + "Writing to Vault" + Color.END)
        while (True):
            label = input("Enter label:       ")
            userLogin = input("Enter login info:  ")
            userPassword = getpass.getpass("Enter password:    ")
            confirmPassword = getpass.getpass("Confirm password:  ")
            if (userPassword != confirmPassword):
                print(Color.FAIL + "Warning: " + Color.END + "passwords do not match")
            else:
                print(Color.SUCCESS + "Success " + Color.END)
                break
        f.write(label + "\n" + userLogin + "\n" + userPassword + "\n")
        f.close()

    # generate password
    if (generateFlag == True):
        f = open("vault.txt", "a")
        f.write("\n")
        print(Color.BOLD + "Generating Password" + Color.END)
        label = input("Enter label:              ")
        userLogin = input("Enter login info:         ")
        password = input("Enter unhashed password:  ")
        hashedPassword = ""
        randomNumber = random.randint(1, 5)    
        if (randomNumber == 1):
            hashedPassword = hashlib.sha256(password.encode())
        elif (randomNumber == 2):
            hashedPassword = hashlib.sha384(password.encode())
        elif (randomNumber == 3):
            hashedPassword = hashlib.sha224(password.encode())
        elif (randomNumber == 4):
            hashedPassword = hashlib.sha512(password.encode())
        else:
            hashedPassword = hashlib.sha1(password.encode())
        hexValuePassword = hashedPassword.hexdigest()
        print("Hashed Password:          " + str(hexValuePassword))
        f.write(label + "\n" + userLogin + "\n" + hexValuePassword + "\n")
        f.close()

    # manually edit vault
    if (sudoFlag == True):
        f = open("vault.txt", "w")                 
        print(Color.BOLD + "Sudo Enabled" + Color.END)

        ADMIN_PASS = "s66757NH"
        adminPassword = ""
        confirmAdminPassword = ""
        while ((adminPassword.lower() != "x") or (confirmAdminPassword.lower() != "x")):
            adminPassword = getpass.getpass("Enter admin password:  ")
            if (adminPassword != ADMIN_PASS):
                print(Color.FAIL + "Error: " + Color.END + "incorrect admin password")
                sys.exit(1)
            
            confirmAdminPassword = getpass.getpass("Confirm password:      ")
            if (adminPassword != confirmAdminPassword):
                print(Color.FAIL + "Warning: " + Color.END + "passwords do not match")
            else:
                break
        
        choices  = "[0] Emacs"
        choices += "\n[1] Vim"
        choices += "\n[2] Nano"
        print(choices)
        userChoice = int(input("Select text editor of choice: "))

        textEditor = ""
        if (userChoice == 0):
            textEditor = "emacs"
        elif (userChoice == 1):
            textEditor = "vim"
        elif (userChoice == 2):
            textEditor = "nano"

        if (userChoice not in (0, 1, 2)):
            print(Color.FAIL + "Warning: " + Color.END + "Invalid choice. Opening with Emacs")
            textEditor = "emacs"
        print("Opening with " + str(textEditor).capitalize())
        time.sleep(1)

        if (os.path.exists("vault.txt") == False):
            sys.stderr.write(Color.FAIL + " Error: " + Color.END + "vault.txt does not exist")
            sys.exit(1)
        os.system(textEditor + " vault.txt")
        f.close()

    os.chmod("vault.txt", 0o100)            # make vault.txt read-only
    if (os.path.exists("#vault.txt#") == True):
        os.remove("#vault.txt#")
    print("\nExiting...\n")
    sys.exit(0)

if __name__ == "__main__":
    main(sys.argv[1:])
