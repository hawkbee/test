#include <gtk/gtk.h>


int main(int argc, char *argv[])
{
	GtkWidget *window, *button;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(window), "StockButton");

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	gtk_widget_set_size_request(window, 250, 100);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	button = gtk_button_new_from_stock(GTK_STOCK_CLOSE);

	g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(gtk_widget_destroy), (gpointer)button);

	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show_all(window);

	gtk_main();

	return (0);
}
