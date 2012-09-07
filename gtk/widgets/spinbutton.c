#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkWidget *window, *spin_int, *spin_float, *vbox;
	GtkAdjustment *integer, *float_pt;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Spin button");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_set_size_request(window, 150, 100);

	integer = GTK_ADJUSTMENT(gtk_adjustment_new(5.0, 0.0, 10.0, 1.0, 2.0, 0));
	float_pt = GTK_ADJUSTMENT(gtk_adjustment_new(0.5, 0.0, 1.0, 0.1, 0.5, 0));

	spin_int = gtk_spin_button_new(integer, 1.0, 0);
	spin_float = gtk_spin_button_new(float_pt, 0.1, 1);

	vbox = gtk_vbox_new(FALSE, 5);
	gtk_box_pack_start_defaults(GTK_BOX(vbox), spin_int);
	gtk_box_pack_start_defaults(GTK_BOX(vbox), spin_float);

	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show_all(window);
	gtk_main();
	return (0);
}
