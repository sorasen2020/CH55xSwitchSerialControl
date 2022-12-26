#include "USBconstant.h"

#define EMULATE_PROCON

//Device descriptor
__code uint8_t DevDesc[] = {
  0x12, 0x01,
  0x00, 0x02,              //USB spec release number in BCD format, USB1.1 (0x10, 0x01).
  0x00, 0x00, 0x00,        //bDeviceClass, bDeviceSubClass, bDeviceProtocol
  0x40,                    //bNumConfigurations
#ifdef EMULATE_PROCON
  0x7E, 0x05, 0x09, 0x20,
#else
  0x0D, 0x0F, 0x92, 0x00,  // VID PID
#endif
  0x00, 0x01,              //version
  0x01, 0x02, 0x03,        //bString
  0x01                     //bNumConfigurations
};

__code uint16_t DevDescLen = sizeof(DevDesc);

__code uint8_t CfgDesc[] = {
  0x09, 0x02, sizeof(CfgDesc) & 0xff, sizeof(CfgDesc) >> 8,
  0x02, 0x01, 0x00, 0xA0, 0xFA,  //Configuration descriptor (1 interface)

  0x09, 0x04, 0x00, 0x00, 0x01, 0x03, 0x01, 0x01, 0x00,                                          // HID Keyboard, 2 endpoints
  0x09, 0x21, 0x11, 0x01, 0x00, 0x01, 0x22, sizeof(ReportDesc) & 0xff, sizeof(ReportDesc) >> 8,  //HID Descriptor
  0x07, 0x05, 0x81, 0x03, 0x40, 0x00, 0x01,

  0x09, 0x04, 0x01, 0x00,
#ifdef EMULATE_PROCON
  0x02,
#else
  0x01,
#endif
  0x03, 0x00, 0x00, 0x00,                                            // HID Keyboard, 2 endpoints
  0x09, 0x21, 0x01, 0x01, 0x00, 0x01, 0x22, sizeof(ReportDesc2) & 0xff, sizeof(ReportDesc2) >> 8,  //HID Descriptor
  0x07, 0x05, 0x82, 0x03, 0x40, 0x00, 0x01,                                                        //endpoint descriptor
#ifdef EMULATE_PROCON
  0x07, 0x05, 0x02, 0x03, 0x40, 0x00, 0x01
#endif
};

__code uint8_t HidDesc[] = {
  // HID Keyboard, 2 endpoints
  0x09, 0x21, 0x11, 0x01, 0x00, 0x01, 0x22, sizeof(ReportDesc) & 0xff, sizeof(ReportDesc) >> 8,  //HID Descriptor                                                    //endpoint descriptor
};

__code uint16_t HidDescLen = sizeof(HidDesc);

__code uint16_t ReportDescLen = sizeof(ReportDesc);

__code uint8_t ReportDesc[] = {
    //  Keyboard
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  47 */
    0x09, 0x06,                      /* USAGE (Keyboard) */
    0xa1, 0x01,                      /* COLLECTION (Application) */
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */

    /* Keyboard Modifiers (shift, alt, ...) */
    0x19, 0xe0,                      /*   USAGE_MINIMUM (Keyboard LeftControl) */
    0x29, 0xe7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */
    0x25, 0x01,                      /*   LOGICAL_MAXIMUM (1) */
    0x75, 0x01,                      /*   REPORT_SIZE (1) */
	0x95, 0x08,                      /*   REPORT_COUNT (8) */
    0x81, 0x02,                      /*   INPUT (Data,Var,Abs) */

    /* Reserved byte, used for consumer reports, only works with linux */
	0x05, 0x0C,             		 /*   Usage Page (Consumer) */
    0x95, 0x01,                      /*   REPORT_COUNT (1) */
    0x75, 0x08,                      /*   REPORT_SIZE (8) */
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */
    0x26, 0xFF, 0x00,                /*   LOGICAL_MAXIMUM (255) */
    0x19, 0x00,                      /*   USAGE_MINIMUM (0) */
    0x29, 0xFF,                      /*   USAGE_MAXIMUM (255) */
    0x81, 0x00,                      /*   INPUT (Data,Ary,Abs) */

	/* 5 LEDs for num lock etc, 3 left for advanced, custom usage */
	0x05, 0x08,						 /*   USAGE_PAGE (LEDs) */
	0x19, 0x01,						 /*   USAGE_MINIMUM (Num Lock) */
	0x29, 0x08,						 /*   USAGE_MAXIMUM (Kana + 3 custom)*/
	0x95, 0x08,						 /*   REPORT_COUNT (8) */
	0x75, 0x01,						 /*   REPORT_SIZE (1) */
	0x91, 0x02,						 /*   OUTPUT (Data,Var,Abs) */

    /* 6 Keyboard keys */
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */
    0x95, 0x06,                      /*   REPORT_COUNT (6) */
    0x75, 0x08,                      /*   REPORT_SIZE (8) */
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */
    0x26, 0xE7, 0x00,                /*   LOGICAL_MAXIMUM (231) */
    0x19, 0x00,                      /*   USAGE_MINIMUM (Reserved (no event indicated)) */
    0x29, 0xE7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */
    0x81, 0x00,                      /*   INPUT (Data,Ary,Abs) */

    /* End */
    0xc0                            /* END_COLLECTION */
};

__code uint16_t ReportDescLen2 = sizeof(ReportDesc2);

__code uint8_t ReportDesc2[] = {
#ifdef EMULATE_PROCON
0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
0x15, 0x00,        // Logical Minimum (0)
0x09, 0x04,        // Usage (Joystick)
0xA1, 0x01,        // Collection (Application)
0x85, 0x30,        //   Report ID (48)
0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
0x05, 0x09,        //   Usage Page (Button)
0x19, 0x01,        //   Usage Minimum (0x01)
0x29, 0x0A,        //   Usage Maximum (0x0A)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x01,        //   Logical Maximum (1)
0x75, 0x01,        //   Report Size (1)
0x95, 0x0A,        //   Report Count (10)
0x55, 0x00,        //   Unit Exponent (0)
0x65, 0x00,        //   Unit (None)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x05, 0x09,        //   Usage Page (Button)
0x19, 0x0B,        //   Usage Minimum (0x0B)
0x29, 0x0E,        //   Usage Maximum (0x0E)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x01,        //   Logical Maximum (1)
0x75, 0x01,        //   Report Size (1)
0x95, 0x04,        //   Report Count (4)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x75, 0x01,        //   Report Size (1)
0x95, 0x02,        //   Report Count (2)
0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x0B, 0x01, 0x00, 0x01, 0x00,  //   Usage (0x010001)
0xA1, 0x00,        //   Collection (Physical)
0x0B, 0x30, 0x00, 0x01, 0x00,  //     Usage (0x010030)
0x0B, 0x31, 0x00, 0x01, 0x00,  //     Usage (0x010031)
0x0B, 0x32, 0x00, 0x01, 0x00,  //     Usage (0x010032)
0x0B, 0x35, 0x00, 0x01, 0x00,  //     Usage (0x010035)
0x15, 0x00,        //     Logical Minimum (0)
0x27, 0xFF, 0xFF, 0x00, 0x00,  //     Logical Maximum (65534)
0x75, 0x10,        //     Report Size (16)
0x95, 0x04,        //     Report Count (4)
0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0xC0,              //   End Collection
0x0B, 0x39, 0x00, 0x01, 0x00,  //   Usage (0x010039)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x07,        //   Logical Maximum (7)
0x35, 0x00,        //   Physical Minimum (0)
0x46, 0x3B, 0x01,  //   Physical Maximum (315)
0x65, 0x14,        //   Unit (System: English Rotation, Length: Centimeter)
0x75, 0x04,        //   Report Size (4)
0x95, 0x01,        //   Report Count (1)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x05, 0x09,        //   Usage Page (Button)
0x19, 0x0F,        //   Usage Minimum (0x0F)
0x29, 0x12,        //   Usage Maximum (0x12)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x01,        //   Logical Maximum (1)
0x75, 0x01,        //   Report Size (1)
0x95, 0x04,        //   Report Count (4)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x75, 0x08,        //   Report Size (8)
0x95, 0x34,        //   Report Count (52)
0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
0x85, 0x21,        //   Report ID (33)
0x09, 0x01,        //   Usage (0x01)
0x75, 0x08,        //   Report Size (8)
0x95, 0x3F,        //   Report Count (63)
0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x85, 0x81,        //   Report ID (-127)
0x09, 0x02,        //   Usage (0x02)
0x75, 0x08,        //   Report Size (8)
0x95, 0x3F,        //   Report Count (63)
0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x85, 0x01,        //   Report ID (1)
0x09, 0x03,        //   Usage (0x03)
0x75, 0x08,        //   Report Size (8)
0x95, 0x3F,        //   Report Count (63)
0x91, 0x83,        //   Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Volatile)
0x85, 0x10,        //   Report ID (16)
0x09, 0x04,        //   Usage (0x04)
0x75, 0x08,        //   Report Size (8)
0x95, 0x3F,        //   Report Count (63)
0x91, 0x83,        //   Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Volatile)
0x85, 0x80,        //   Report ID (-128)
0x09, 0x05,        //   Usage (0x05)
0x75, 0x08,        //   Report Size (8)
0x95, 0x3F,        //   Report Count (63)
0x91, 0x83,        //   Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Volatile)
0x85, 0x82,        //   Report ID (-126)
0x09, 0x06,        //   Usage (0x06)
0x75, 0x08,        //   Report Size (8)
0x95, 0x3F,        //   Report Count (63)
0x91, 0x83,        //   Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Volatile)
0xC0
#else
  0x05, 0x01, 0x09, 0x05, 0xa1, 0x01, 0x15, 0x00, 0x25, 0x01, 0x35, 0x00,
  0x45, 0x01, 0x75, 0x01, 0x95, 0x10, 0x05, 0x09, 0x19, 0x01, 0x29, 0x10,
  0x81, 0x02, 0x05, 0x01, 0x25, 0x07, 0x46, 0x3b, 0x01, 0x75, 0x04, 0x95,
  0x01, 0x65, 0x14, 0x09, 0x39, 0x81, 0x42, 0x65, 0x00, 0x95, 0x01, 0x81,
  0x01, 0x26, 0xff, 0x00, 0x46, 0xff, 0x00, 0x09, 0x30, 0x09, 0x31, 0x09,
  0x32, 0x09, 0x35, 0x75, 0x08, 0x95, 0x04, 0x81, 0x02, 0x06, 0x00, 0xff,
  0x09, 0x20, 0x95, 0x01, 0x81, 0x02, 0x0a, 0x21, 0x26, 0x95, 0x08, 0x91,
  0x02, 0xc0
#endif
};

__code uint16_t CfgDescLen = sizeof(CfgDesc);

//String Descriptors
__code uint8_t LangDes[] = { 0x04, 0x03, 0x09, 0x04 };  //Language Descriptor
__code uint16_t LangDesLen = sizeof(LangDes);
__code uint8_t Prod_Des[] = {  //Produce String Descriptor
#ifdef EMULATE_PROCON
  0x1E, 0x03,
  'P', 0x00, 'r', 0x00, 'o', 0x00, ' ', 0x00, 
  'C', 0x00, 'o', 0x00, 'n', 0x00, 't', 0x00, 'r', 0x00, 'o', 0x00, 'l', 0x00, 'l', 0x00, 'e', 0x00, 'r', 0x00
#else
  0x24, 0x03,
  'P', 0x00, 'O', 0x00, 'K', 0x00, 'K', 0x00, 'E', 0x00, 'N', 0x00, ' ', 0x00,
  'C', 0x00, 'O', 0x00, 'N', 0x00, 'T', 0x00, 'R', 0x00, 'O', 0x00, 'L', 0x00, 'L', 0x00, 'E', 0x00, 'R', 0x00
#endif
};
__code uint16_t Prod_DesLen = sizeof(Prod_Des);

__code uint8_t Manuf_Des[] = {
#ifdef EMULATE_PROCON
  0x26, 0x03,
  'N', 0x00, 'i', 0x00, 'n', 0x00, 't', 0x00, 'e', 0x00, 'n', 0x00, 'd', 0x00, 'o', 0x00, ' ', 0x00,
  'C', 0x00, 'o', 0x00, '.', 0x00, ',', 0x00, ' ', 0x00, 'L', 0x00, 't', 0x00, 'd', 0x00, '.', 0x00
#else
  0x1C, 0x03,
  'H', 0x00, 'O', 0x00, 'R', 0x00, 'I', 0x00, ' ', 0x00,
  'C', 0x00, 'O', 0x00, '.', 0x00, ',', 0x00, 'L', 0x00, 'T', 0x00, 'D', 0x00, '.', 0x00
#endif
};
__code uint16_t Manuf_DesLen = sizeof(Manuf_Des);

__code uint8_t Seri_Des[] = {
  0x4, 0x03,
  '0', 0x00
};
__code uint16_t Seri_DesLen = sizeof(Seri_Des);