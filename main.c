#include <gtk/gtk.h>

/* Callback function - Signal Handler 
 * 
 * -The first argument of the signal handler will always be a pointer to the widget that
generated the signal
 * -The callback_data argument will always be the last argument passed to the signal handler (gpointer)
 * -Any arguments that are specific to the widget or to the signal will occur between the
first and last arguments of the signal handler
 * 
 */
void calendar_day_selected(GtkWidget* calendar, gpointer k) 
{
    guint day, month, year;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    printf("Day is selected! selected day : %d \n", day);
}

void window(GtkApplication* app, gpointer user_data)
{
	GtkWidget *window;
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "ToothBrushing Calendar");
	gtk_window_set_default_size(GTK_WINDOW(window), 600,500);
        
    GtkWidget* label = gtk_label_new("Calendar");    
    GtkWidget* vlayout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget* button = gtk_button_new_with_label("Select");
    GtkWidget* calendar = gtk_calendar_new();
    
    //gtk_label_set_text(GTK_LABEL(label), "AAAAAAAAA");
    
    gtk_box_pack_start(GTK_BOX(vlayout), label, FALSE, FALSE,0);
    gtk_box_pack_start(GTK_BOX(vlayout), calendar, FALSE, FALSE,0);
    gtk_box_pack_start(GTK_BOX(vlayout), button, FALSE, FALSE,0);
    gtk_container_add(GTK_CONTAINER(window), vlayout);

    guint day=1,month=1,year=2021;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    gtk_calendar_mark_day(calendar, 5);
    
    // signal-slot
    int k = 99;
    g_signal_connect(calendar,                                      /* Widget */
                     "day-selected",                                /* Signal */
                     G_CALLBACK(calendar_day_selected),             /* Signal Handler */
                     (gpointer) k);                                 /* Private Data */
    
    // set stylesheet
    GtkCssProvider *provider = gtk_css_provider_new ();
    GdkDisplay *display = gdk_display_get_default ();
    GdkScreen *screen = gdk_display_get_default_screen (display);   
    gtk_css_provider_load_from_data (provider,
                            "button, entry {"
                            "  color: #ff00ea;"
                            "  font: 20px \"Comic Sans\";"
                            "}", -1, NULL);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref (provider);
    
    
    gtk_widget_show_all(window);
}


int main(int argc, char **argv)
{
	GtkApplication *app;
	app = gtk_application_new("org.gtk.hello", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(window), NULL);
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	
	return 0;
}
 
