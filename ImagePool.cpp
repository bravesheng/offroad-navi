#include "ImagePool.h"

QPixmap* ImageArray[IMG_ID_NUMS];

bool PrepareImagePool(void)
{
	ImageArray[IMG_BACKGROUND_STD] = new QPixmap(":/images/background_std.png");
	ImageArray[IMG_BTN_RETURN] = new QPixmap(":/images/btn_return.png");
	ImageArray[IMG_BTN_RETURN_DOWN] = new QPixmap(":/images/btn_return_down.png");
	ImageArray[IMG_BTN_EDIT_UP] = new QPixmap(":/images/btn_edit_up.png");
	ImageArray[IMG_BTN_EDIT_DOWN] = new QPixmap(":/images/btn_edit_down.png");
	ImageArray[IMG_BTN_ELEVATION_UP] = new QPixmap(":/images/btn_elevation_up.png");
	ImageArray[IMG_BTN_ELEVATION_DOWN] = new QPixmap(":/images/btn_elevation_down.png");
	ImageArray[IMG_BTN_HOME_UP] = new QPixmap(":/images/btn_home_up.png");
	ImageArray[IMG_BTN_HOME_DOWN] = new QPixmap(":/images/btn_home_down.png");
	ImageArray[IMG_BTN_SHARE_UP] = new QPixmap(":/images/btn_share_up.png");
	ImageArray[IMG_BTN_SHARE_DOWN] = new QPixmap(":/images/btn_share_down.png");
	ImageArray[IMG_BTN_TARGET_UP] = new QPixmap(":/images/btn_target_up.png");
	ImageArray[IMG_BTN_TARGET_DOWN] = new QPixmap(":/images/btn_target_down.png");
	ImageArray[IMG_BTN_VIEWMAP_UP] = new QPixmap(":/images/btn_viewmap_up.png");
	ImageArray[IMG_BTN_VIEWMAP_DOWN] = new QPixmap(":/images/btn_viewmap_down.png");

	ImageArray[IMG_GADGET_SPEED] = new QPixmap(":/images/gadget_speed.png");
	ImageArray[IMG_GADGET_ALTITUDE] = new QPixmap(":/images/gadget_altitude.png");
	ImageArray[IMG_GADGET_LENGTH] = new QPixmap(":/images/gadget_length.png");
	ImageArray[IMG_GADGET_TIME] = new QPixmap(":/images/gadget_time.png");
	ImageArray[IMG_GADGET_ARROW] = new QPixmap(":/images/gadget_arrow.png");
	ImageArray[IMG_GADGET_STRING] = new QPixmap(":/images/gadget_string.png");
	ImageArray[IMG_GADGET_COMPASS] = new QPixmap(":/images/gadget_compass_body.png");
	ImageArray[IMG_GADGET_GPS_PLOT] = NULL;//
	ImageArray[IMG_GADGET_GPS_SIGNAL] = new QPixmap(":/images/gadget_GPS.png");
	ImageArray[IMG_GADGET_ELEVATION_PLOT] = new QPixmap(":/images/gadget_ElevationPlot.png");
	ImageArray[IMG_GADGET_COMPASS_GRADUATION] = new QPixmap(":/images/gadget_compass_graduation.png");
	ImageArray[IMG_GADGET_HEARTBEAT] = new QPixmap(":/images/gadget_heartbeat.png");
	ImageArray[IMG_GADGET_BATTERY] = new QPixmap(":/images/gadget_battery.png");

	ImageArray[IMG_BAR_MAIN_MENU] = new QPixmap(":/images/bar_main_menu.png");
	ImageArray[IMG_BAR_GADGET_LIST] = new QPixmap(":/images/bar_gadget_list.png");

	ImageArray[IMG_LIST_BK] = new QPixmap(":/images/listbox_BK.png");
	ImageArray[IMG_LIST_ITEM] = new QPixmap(":images/listbox_up.png");
	ImageArray[IMG_LIST_ITEM_DOWN] = new QPixmap(":images/listbox_down.png");
	ImageArray[IMG_LIST_ITEM_SELECTED] = new QPixmap(":images/listbox_sel.png");
	ImageArray[IMG_LIST_ITEM_SELECTED1] = new QPixmap(":images/listbox_sel1.png");

	ImageArray[IMG_EDIT_BK] = new QPixmap(":/images/edit_BK.png");
	ImageArray[IMG_EDIT_DELETE_UP] = new QPixmap(":/images/edit_delete_up.png");
	ImageArray[IMG_EDIT_DELETE_DOWN] = new QPixmap(":/images/edit_delete_down.png");
	ImageArray[IMG_EDIT_EDITBOX_BK] = new QPixmap(":/images/edit_editbox_BK.png");
	ImageArray[IMG_EDIT_ICON_UP] = new QPixmap(":/images/edit_icon_up.png");
	ImageArray[IMG_EDIT_ICON_DOWN] = new QPixmap(":/images/edit_icon_down.png");
	ImageArray[IMG_EDIT_NAME_UP] = new QPixmap(":/images/edit_name_up.png");
	ImageArray[IMG_EDIT_NAME_DOWN] = new QPixmap(":/images/edit_name_down.png");
	ImageArray[IMG_EDIT_SAVE_UP] = new QPixmap(":/images/edit_save_up.png");
	ImageArray[IMG_EDIT_SAVE_DOWN] = new QPixmap(":/images/edit_save_down.png");

	ImageArray[IMG_KEYPAD_BK] = new QPixmap(":/images/keypad_BK.png");
	ImageArray[IMG_KEYPAD_KEY1_UP] = new QPixmap(":/images/keypad_key1_up.png");
	ImageArray[IMG_KEYPAD_KEY1_DOWN] = new QPixmap(":/images/keypad_key1_down.png");
	ImageArray[IMG_KEYPAD_KEY2_UP] = new QPixmap(":/images/keypad_key2_up.png");
	ImageArray[IMG_KEYPAD_KEY2_DOWN] = new QPixmap(":/images/keypad_key2_down.png");
	ImageArray[IMG_KEYPAD_KEY3_UP] = new QPixmap(":/images/keypad_key3_up.png");
	ImageArray[IMG_KEYPAD_KEY3_DOWN] = new QPixmap(":/images/keypad_key3_down.png");
	ImageArray[IMG_KEYPAD_KEY4_UP] = new QPixmap(":/images/keypad_key4_up.png");
	ImageArray[IMG_KEYPAD_KEY4_DOWN] = new QPixmap(":/images/keypad_key4_down.png");
	ImageArray[IMG_KEYPAD_KEY5_UP] = new QPixmap(":/images/keypad_key5_up.png");
	ImageArray[IMG_KEYPAD_KEY5_DOWN] = new QPixmap(":/images/keypad_key5_down.png");

	ImageArray[IMG_ICON_TRIP_COMPUTER] = new QPixmap(":/images/icon_trip_computer.png");
	*ImageArray[IMG_ICON_TRIP_COMPUTER] = ImageArray[IMG_ICON_TRIP_COMPUTER]->scaledToHeight(50);
	ImageArray[IMG_ICON_COMPASS] = new QPixmap(":/images/icon_compass.png");
	*ImageArray[IMG_ICON_COMPASS] = ImageArray[IMG_ICON_COMPASS]->scaledToHeight(50);
	ImageArray[IMG_ICON_ALTIMETER] = new QPixmap(":/images/icon_altimeter.png");
	*ImageArray[IMG_ICON_ALTIMETER] = ImageArray[IMG_ICON_ALTIMETER]->scaledToHeight(50);
	ImageArray[IMG_ICON_WAYPOINT] = new QPixmap(":/images/icon_waypoint.png");
	*ImageArray[IMG_ICON_WAYPOINT] = ImageArray[IMG_ICON_WAYPOINT]->scaledToHeight(50);
	ImageArray[IMG_ICON_TRACK] = new QPixmap(":/images/icon_track.png");
	*ImageArray[IMG_ICON_TRACK] = ImageArray[IMG_ICON_TRACK]->scaledToHeight(50);
	ImageArray[IMG_ICON_SETTINGS] = new QPixmap(":/images/icon_setting.png");
	*ImageArray[IMG_ICON_SETTINGS] = ImageArray[IMG_ICON_SETTINGS]->scaledToHeight(50);
	ImageArray[IMG_ICON_GPS] = new QPixmap(":/images/icon_gps.png");
	*ImageArray[IMG_ICON_GPS] = ImageArray[IMG_ICON_GPS]->scaledToHeight(50);
	ImageArray[IMG_ICON_ADD_WAYPOINT] = new QPixmap(":/images/icon_add_waypoint.png");
	*ImageArray[IMG_ICON_ADD_WAYPOINT] = ImageArray[IMG_ICON_ADD_WAYPOINT]->scaledToHeight(50);
	ImageArray[IMG_ICON_EXIT] = new QPixmap(":/images/icon_exit.png");
	*ImageArray[IMG_ICON_EXIT] = ImageArray[IMG_ICON_EXIT]->scaledToHeight(50);
	ImageArray[IMG_SETTING_BK] = new QPixmap(":/images/setting_bk.png");
	ImageArray[IMG_SETTING_RETURN_UP] = new QPixmap(":/images/setting_return_up.png");
	ImageArray[IMG_SETTING_RETURN_DOWN] = new QPixmap(":/images/setting_return_down.png");
	ImageArray[IMG_SETTING_LIST_UP] = new QPixmap(":/images/setting_list_up.png");
	ImageArray[IMG_SETTING_LIST_DOWN] = new QPixmap(":/images/setting_list_down.png");
	ImageArray[IMG_SETTING_LIST_SEL] = new QPixmap(":/images/setting_list_sel.png");
	ImageArray[IMG_SETTING_LIST_SEL1] = new QPixmap(":/images/setting_list_sel1.png");
	ImageArray[IMG_SETTING_NEXT_ICON] = new QPixmap(":/images/setting_next_icon.png");
	ImageArray[IMG_SETTING_SELECT_ICON] = new QPixmap(":/images/setting_select_icon.png");
	ImageArray[IMG_SETTING_UNSELECT_ICON] = new QPixmap(":/images/setting_unselect_icon.png");
	ImageArray[IMG_SETTING_LIST_ICON1] = new QPixmap(":/images/setting_listicon1.png");
	ImageArray[IMG_SETTING_LIST_ICON2] = new QPixmap(":/images/setting_listicon2.png");
	ImageArray[IMG_SETTING_LIST_ICON3] = new QPixmap(":/images/setting_listicon3.png");
	ImageArray[IMG_SETTING_LIST_ICON4] = new QPixmap(":/images/setting_listicon4.png");
	ImageArray[IMG_SETTING_SWITCH_ON] = new QPixmap(":/images/setting_switch_on.png");
	ImageArray[IMG_SETTING_SWITCH_OFF] = new QPixmap(":/images/setting_switch_off.png");

	ImageArray[IMG_TRACK_ICON_BACK] = new QPixmap(":/images/track_icon_back.png");
	ImageArray[IMG_TRACK_ICON_C1] = new QPixmap(":/images/track_icon_C1.png");
	ImageArray[IMG_TRACK_ICON_C2] = new QPixmap(":/images/track_icon_C2.png");
	ImageArray[IMG_TRACK_ICON_C3] = new QPixmap(":/images/track_icon_C3.png");
	ImageArray[IMG_TRACK_ICON_C4] = new QPixmap(":/images/track_icon_C4.png");
	ImageArray[IMG_TRACK_ICON_C5] = new QPixmap(":/images/track_icon_C5.png");
	ImageArray[IMG_TRACK_ICON_C6] = new QPixmap(":/images/track_icon_C6.png");
	ImageArray[IMG_TRACK_ICON_C7] = new QPixmap(":/images/track_icon_C7.png");
	ImageArray[IMG_TRACK_ICON_C8] = new QPixmap(":/images/track_icon_C8.png");
	ImageArray[IMG_TRACK_ICON_C9] = new QPixmap(":/images/track_icon_C9.png");
	ImageArray[IMG_TRACK_ICON_C10] = new QPixmap(":/images/track_icon_C10.png");
	ImageArray[IMG_TRACK_LIST_ICON1] = new QPixmap(":/images/track_listicon1.png");
	ImageArray[IMG_TRACK_LIST_ICON2] = new QPixmap(":/images/track_listicon2.png");
	ImageArray[IMG_TRACK_LIST_ICON3] = new QPixmap(":/images/track_listicon3.png");
	ImageArray[IMG_TRACK_LIST_ICON4] = new QPixmap(":/images/track_listicon4.png");
	ImageArray[IMG_TRACK_LIST_ICON5] = new QPixmap(":/images/track_listicon5.png");
	ImageArray[IMG_TRACK_LIST_ICON6] = new QPixmap(":/images/track_listicon6.png");
	ImageArray[IMG_TRACK_LIST_ICON7] = new QPixmap(":/images/track_listicon7.png");
	ImageArray[IMG_TRACK_LIST_ICON8] = new QPixmap(":/images/track_listicon8.png");
	ImageArray[IMG_TRACK_LIST_ICON9] = new QPixmap(":/images/track_listicon9.png");
	ImageArray[IMG_TRACK_LIST_ICON10] = new QPixmap(":/images/track_listicon10.png");

	ImageArray[IMG_WAYPOINT_DIRECT_ICON] = new QPixmap(":/images/waypoint_direct_icon.png");
	ImageArray[IMG_WAYPOINT_ICON_BACK] = new QPixmap(":/images/waypoint_icon_back.png");
	ImageArray[IMG_WAYPOINT_ICON_C1] = new QPixmap(":/images/waypoint_icon_C1.png");
	ImageArray[IMG_WAYPOINT_ICON_C2] = new QPixmap(":/images/waypoint_icon_C2.png");
	ImageArray[IMG_WAYPOINT_ICON_C3] = new QPixmap(":/images/waypoint_icon_C3.png");
	ImageArray[IMG_WAYPOINT_ICON_C4] = new QPixmap(":/images/waypoint_icon_C4.png");
	ImageArray[IMG_WAYPOINT_ICON_C5] = new QPixmap(":/images/waypoint_icon_C5.png");
	ImageArray[IMG_WAYPOINT_ICON_C6] = new QPixmap(":/images/waypoint_icon_C6.png");
	ImageArray[IMG_WAYPOINT_ICON_C7] = new QPixmap(":/images/waypoint_icon_C7.png");
	ImageArray[IMG_WAYPOINT_ICON_C8] = new QPixmap(":/images/waypoint_icon_C8.png");
	ImageArray[IMG_WAYPOINT_ICON_C9] = new QPixmap(":/images/waypoint_icon_C9.png");
	ImageArray[IMG_WAYPOINT_ICON_C10] = new QPixmap(":/images/waypoint_icon_C10.png");
	ImageArray[IMG_WAYPOINT_LIST_ICON1] = new QPixmap(":/images/waypoint_listicon1.png");
	ImageArray[IMG_WAYPOINT_LIST_ICON2] = new QPixmap(":/images/waypoint_listicon2.png");
	ImageArray[IMG_WAYPOINT_LIST_ICON3] = new QPixmap(":/images/waypoint_listicon3.png");
	ImageArray[IMG_WAYPOINT_LIST_ICON4] = new QPixmap(":/images/waypoint_listicon4.png");
	ImageArray[IMG_WAYPOINT_LIST_ICON5] = new QPixmap(":/images/waypoint_listicon5.png");
	ImageArray[IMG_WAYPOINT_LIST_ICON6] = new QPixmap(":/images/waypoint_listicon6.png");
	ImageArray[IMG_WAYPOINT_LIST_ICON7] = new QPixmap(":/images/waypoint_listicon7.png");
	ImageArray[IMG_WAYPOINT_LIST_ICON8] = new QPixmap(":/images/waypoint_listicon8.png");
	ImageArray[IMG_WAYPOINT_LIST_ICON9] = new QPixmap(":/images/waypoint_listicon9.png");
	ImageArray[IMG_WAYPOINT_LIST_ICON10] = new QPixmap(":/images/waypoint_listicon10.png");

	return true;
}

void ReleaseImagePool(void)
{
	for(int i=0; i < IMG_ID_NUMS; i++)
	{
		if(ImageArray[i] != NULL)
		{
			delete ImageArray[i];
			ImageArray[i] = NULL;
		}
	}
}

QPixmap* GetImg(IMG_ID id)
{
	if(id == IMG_NULL)
	{
		return NULL;
	}
	return ImageArray[id];
}