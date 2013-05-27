#ifndef ROGLOBALDEFINE_H
#define ROGLOBALDEFINE_H

#define __nWidth__	320
#define __nHeight__	240

enum {
    BUTTON_UP = 0,
    BUTTON_DOWN,
    BUTTON_SEL,
    BUTTON_DISABLE,
	BUTTON_IMG_COUNT
};

const QString g_strTitleFontFamily    ("tahoma");
const int     g_iTitleFontPointSize   (14);
const int     g_iListFontPointSize    (10);

#define __TitleTextColor__            (Qt::white)
#define __TitleTextAlignFlag__        (Qt::AlignCenter)

#define __TextBlackColor__			  (Qt::black)

//Button images
const QString g_strImgRoot         (":/images/");

const QRect   g_rectTitle             (  40,   0, 215,  34);

const QString g_strButtonQuitUp       (g_strImgRoot + "setting_return_up.png");
const QString g_strButtonQuitDown     (g_strImgRoot + "setting_return_down.png");
const QRect   g_rectButtonQuit        (   0,   0,  40,  32);

const QString g_strButtonHomeUp       (g_strImgRoot + "btn_home_up.png");
const QString g_strButtonHomeDown     (g_strImgRoot + "btn_home_down.png");
const QRect   g_rectButtonHome        ( 214,   0,  40,  34);

const QString g_strButtonViewUp       (g_strImgRoot + "btn_viewmap_up.png");
const QString g_strButtonViewDown     (g_strImgRoot + "btn_viewmap_down.png");
const QRect   g_rectButtonView        ( 255,   0,  65,  60);

const QString g_strButtonEditUp       (g_strImgRoot + "btn_edit_up.png");
const QString g_strButtonEditDown     (g_strImgRoot + "btn_edit_down.png");
const QRect   g_rectButtonEdit        ( 255, 120,  65,  60);

const QString g_strButtonShareUp      (g_strImgRoot + "btn_share_up.png");
const QString g_strButtonShareDown    (g_strImgRoot + "btn_share_down.png");
const QRect   g_rectButtonShare       ( 255, 180,  65,  60);

const QString g_strButtonTargetUp     (g_strImgRoot + "btn_share_up.png");
const QString g_strButtonTargetDown   (g_strImgRoot + "btn_target_down.png");
const QRect   g_rectButtonTarget      ( 255,  60,  65,  60);

const QString g_strButtonElevationUp  (g_strImgRoot + "btn_elevation_up.png");
const QString g_strButtonElevationDown(g_strImgRoot + "btn_elevation_down.png");
const QRect   g_rectButtonElevation   ( 255,  60,  65,  60);

//List Box images
const QString g_strListBK            (g_strImgRoot + "listbox_BK.png");

const QString g_strListBoxBaseUp      (g_strImgRoot + "listbox_up.png");
const QString g_strListBoxBaseDown    (g_strImgRoot + "listbox_down.png");
const QString g_strListBoxBaseSel     (g_strImgRoot + "listbox_sel.png");
const QString g_strListBoxBaseSel1    (g_strImgRoot + "listbox_sel1.png");
const QRect   g_rectListBoxBase       (   0,  34, 254, 206);

//Edit Screen images

const QRect   g_rectEditTitle         (  40,   0, 215,  34);
const QString g_strTitleEdit          ("Edit");
const QString g_strEditBackground     (g_strImgRoot + "edit_BK.png");

const QString g_strButtonIconUp       (g_strImgRoot + "edit_icon_up.png");
const QString g_strButtonIconDown     (g_strImgRoot + "edit_icon_down.png");
const QRect   g_rectButtonIcon        (   6,  37,  64,  65);

const QString g_strButtonNameUp       (g_strImgRoot + "edit_name_up.png");
const QString g_strButtonNameDown     (g_strImgRoot + "edit_name_down.png");
const QRect   g_rectButtonName        (  70,  37, 180,  65);

const QString g_strEditButtonSaveUp   (g_strImgRoot + "edit_save_up.png");
const QString g_strEditButtonSaveDown (g_strImgRoot + "edit_save_down.png");
const QRect   g_rectEditButtonSave    ( 255,  60,  65,  60);

const QString g_strEditButtonDelUp    (g_strImgRoot + "edit_delete_up.png");
const QString g_strEditButtonDelDown  (g_strImgRoot + "edit_delete_down.png");
const QRect   g_rectEditButtonDel     ( 255, 120,  65,  60);

//Waypoints Screen
const QString g_strWayPtDB_Path	      ("data\\WaypointDB.db");
const QString g_strTitleWaypoint      ("Waypoint");

const QString g_WayPtListIconPath[10] = {
    (g_strImgRoot + "waypoint_listicon1.png"),
    (g_strImgRoot + "waypoint_listicon2.png"),
    (g_strImgRoot + "waypoint_listicon3.png"),
    (g_strImgRoot + "waypoint_listicon4.png"),
    (g_strImgRoot + "waypoint_listicon5.png"),
    (g_strImgRoot + "waypoint_listicon6.png"),
    (g_strImgRoot + "waypoint_listicon7.png"),
    (g_strImgRoot + "waypoint_listicon8.png"),
    (g_strImgRoot + "waypoint_listicon9.png"),
    (g_strImgRoot + "waypoint_listicon10.png"),
};
const QString g_DirectPath            (g_strImgRoot + "waypoint_direct_icon.png");

// Edit Screen
const QString g_strWayPtBtnIconClr1[10]={ (g_strImgRoot + "waypoint_icon_C1.png"),
                                        (g_strImgRoot + "waypoint_icon_C2.png"),
                                        (g_strImgRoot + "waypoint_icon_C3.png"),
                                        (g_strImgRoot + "waypoint_icon_C4.png"),
                                        (g_strImgRoot + "waypoint_icon_C5.png"),
                                        (g_strImgRoot + "waypoint_icon_C6.png"),
                                        (g_strImgRoot + "waypoint_icon_C7.png"),
                                        (g_strImgRoot + "waypoint_icon_C8.png"),
                                        (g_strImgRoot + "waypoint_icon_C9.png"),
                                        (g_strImgRoot + "waypoint_icon_C10.png") };

const QString g_strWayPtBtnIconClr2     (g_strImgRoot + "waypoint_icon_back.png");

const QRect   g_rectWayPtBtnIconClr[10]={ QRect( 200, 177,  45,  45),
                                        QRect( 152, 177,  45,  45),
                                        QRect( 104, 177,  45,  45),
                                        QRect(  56, 177,  45,  45),
                                        QRect(   8, 177,  45,  45),
                                        QRect( 200, 128,  45,  45),
                                        QRect( 152, 128,  45,  45),
                                        QRect( 104, 128,  45,  45),
                                        QRect(  56, 128,  45,  45),
                                        QRect(   8, 128,  45,  45) };

//Track Screen
//const QString g_strTrackDB_Path		  ("data\\TrackDB.db");
const QString g_strTrackDB_Path		  ("\\MyFlashDisk\\TrackLog");
//const QRect   g_rectTitle             (  40,   0, 215,  34);
const QString g_strTitleTrack         ("Track");


// Edit Screen
const QRect   g_rectEditTrackTitle    (  40,   0, 215,  34);
const QString g_strTitleTrackEdit     ("Edit");

const QString g_strTrackBtnIconClr1[10]={ (g_strImgRoot + "track_icon_C1.png"),
                                        (g_strImgRoot + "track_icon_C2.png"),
                                        (g_strImgRoot + "track_icon_C3.png"),
                                        (g_strImgRoot + "track_icon_C4.png"),
                                        (g_strImgRoot + "track_icon_C5.png"),
                                        (g_strImgRoot + "track_icon_C6.png"),
                                        (g_strImgRoot + "track_icon_C7.png"),
                                        (g_strImgRoot + "track_icon_C8.png"),
                                        (g_strImgRoot + "track_icon_C9.png"),
                                        (g_strImgRoot + "track_icon_C10.png") };

const QString g_strTrackBtnIconClr2     (g_strImgRoot + "track_icon_back.png");

const QRect   g_rectTrackBtnIconClr[10]={
			QRect(   8, 128,  45,  45),
			QRect(  56, 128,  45,  45),
			QRect( 104, 128,  45,  45),
			QRect( 152, 128,  45,  45),
			QRect( 200, 128,  45,  45),
			QRect(   8, 177,  45,  45),
			QRect(  56, 177,  45,  45),
			QRect( 104, 177,  45,  45),
			QRect( 152, 177,  45,  45),
			QRect( 200, 177,  45,  45)
		};

const QString g_strTrackListIconPath[10]={ (g_strImgRoot + "track_listicon1.png"),
                                        (g_strImgRoot + "track_listicon2.png"),
                                        (g_strImgRoot + "track_listicon3.png"),
                                        (g_strImgRoot + "track_listicon4.png"),
                                        (g_strImgRoot + "track_listicon5.png"),
                                        (g_strImgRoot + "track_listicon6.png"),
                                        (g_strImgRoot + "track_listicon7.png"),
                                        (g_strImgRoot + "track_listicon8.png"),
                                        (g_strImgRoot + "track_listicon9.png"),
                                        (g_strImgRoot + "track_listicon10.png")
                                    };

//Setting Screen
const QRect   g_rectSettingTitle      (  40,   0, 240,  34);
const QString g_strTitleSettings      ("Settings");
const QString g_strSettingBK          (g_strImgRoot + "background_std.png");

const QString g_strSetListBaseUp      (g_strImgRoot + "setting_list_up.png");
const QString g_strSetListBaseDown    (g_strImgRoot + "setting_list_down.png");
const QString g_strSetListBaseSel     (g_strImgRoot + "setting_list_sel.png");
const QString g_strSetListBaseSel1    (g_strImgRoot + "setting_list_sel1.png");
const QRect   g_rectSetListBase       (   0,  34, 320, 206);
const QRect   g_rectSetAltListBase    (   0,  80, 320, 206);
const QRect   g_rectSetAntListBase    (   0,  80, 320, 206);

const QString g_ListIcon1Path         (g_strImgRoot + "setting_listicon1.png");
const QString g_ListIcon2Path         (g_strImgRoot + "setting_listicon2.png");
const QString g_ListIcon3Path         (g_strImgRoot + "setting_listicon3.png");
const QString g_ListIcon4Path         (g_strImgRoot + "setting_listicon4.png");

const QString g_NextIconPath          (g_strImgRoot + "setting_next_icon.png");
const QString g_UnSelectIconPath      (g_strImgRoot + "setting_unselect_icon.png");
const QString g_SelectIconPath        (g_strImgRoot + "setting_select_icon.png");

// Units Screen.
const QString g_strTitleUnits      ("Units");

// Altimeter Calibration Screen.
const QString g_strTitleAltimeter      ("Altimeter Calibration");
const QRect   g_rect_Notes           (  40,   50, 240,  34);

// ANT sport screen
const QString g_strTitleANTsport      ("ANT sport");

// System Info Screen.
const QString g_strTitleSysInfo      ("About");
const QRect   g_rectAP_Ver           (  40,   50, 240,  34);
const QRect   g_rectOS_Ver           (  40,   85, 240,  34);
const QRect   g_rectBoot_Ver         (  40,   120, 240,  34);
const QRect   g_rectSN_Ver           (  40,   155, 240,  34);

//Alphabet Keyboard
const QString g_strKeyboardBK         (g_strImgRoot + "keypad_BK.png");
const QRect   g_rectKeyboard          ( 0, 105,  255,  135);
//const QRect   g_rectKeyboard          ( 0, 0,  255,  240);

const QString g_strKey1Up             (g_strImgRoot + "keypad_key1_up.png");
const QString g_strKey1Down           (g_strImgRoot + "keypad_key1_down.png");

const QString g_strKey2Up             (g_strImgRoot + "keypad_key2_up.png");
const QString g_strKey2Down           (g_strImgRoot + "keypad_key2_down.png");

const QString g_strKey3Up             (g_strImgRoot + "keypad_key3_up.png");
const QString g_strKey3Down           (g_strImgRoot + "keypad_key3_down.png");

const QString g_strKey4Up             (g_strImgRoot + "keypad_key4_up.png");
const QString g_strKey4Down           (g_strImgRoot + "keypad_key4_down.png");

const QString g_strKey5Up             (g_strImgRoot + "keypad_key5_up.png");
const QString g_strKey5Down           (g_strImgRoot + "keypad_key5_down.png");

const QString g_strKey6Up             (g_strImgRoot + "keypad_key6_up.png");
const QString g_strKey6Down           (g_strImgRoot + "keypad_key6_down.png");

const QString g_strKey7Up             (g_strImgRoot + "keypad_key7_up.png");
const QString g_strKey7Down           (g_strImgRoot + "keypad_key7_down.png");

const QString g_strKeyDelUp           (g_strImgRoot + "keypad_del_up.png");
const QString g_strKeyDelDown         (g_strImgRoot + "keypad_del_down.png");

const QString g_strKeyEnterUp         (g_strImgRoot + "keypad_enter_up.png");
const QString g_strKeyEnterDown       (g_strImgRoot + "keypad_enter_down.png");

const QString g_strKeySwitchUp        (g_strImgRoot + "keypad_switch_up.png");
const QString g_strKeySwitchDown      (g_strImgRoot + "keypad_switch_down.png");

#endif // ROGLOBALDEFINE_H
