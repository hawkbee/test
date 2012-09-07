#include <gtk/gtk.h>

static void check_toggled(GtkToggleButton *toggle, GtkWidget *toggled)
{
	if (gtk_toggle_button_get_active(toggle))
		gtk_widget_set_sensitive(toggled, TRUE);
	else
		gtk_widget_set_sensitive(toggled, FALSE);
}

int main(int argc, char *argv[])
{
	GtkWidget *window, *vbox, *check1, *check2, *close;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(window), "CheckButton");

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	check1 = gtk_check_button_new_with_label("I am the main option:");
	check2 = gtk_check_button_new_with_label("I rely on the other guy.");

	gtk_widget_set_sensitive(check2, FALSE);

	g_signal_connect(G_OBJECT(check1), "toggled", G_CALLBACK(check_toggled), (gpointer)check2);
	
	close = gtk_button_new_from_stock(GTK_STOCK_CLOSE);

	g_signal_connect_swapped(G_OBJECT(close), "clicked", G_CALLBACK(gtk_widget_destroy), (gpointer)window);

	vbox = gtk_vbox_new(FALSE, 5);

	gtk_box_pack_start(GTK_BOX(vbox), check1, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), check2, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), close, FALSE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(window), vbox);

	gtk_widget_show_all(window);

	gtk_main();

	return (0);
}
