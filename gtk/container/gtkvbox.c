#include <gtk/gtk.h>

#define NAMES_NUM (4)
const gchar* names[] = {"Hawking", "Joe", "Merry", "James"};

int main(int argc, char *argv[])
{
	gint i;
	GtkWidget *window, *vbox;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "VBox");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request(window, 200, -1);

	vbox = gtk_vbox_new(TRUE, 5);

	/* Add four bottons to the vertical box */
	for (i = 0; i < NAMES_NUM; ++i) {
		GtkWidget *button = gtk_button_new_with_label(names[i]);
		gtk_box_pack_start_defaults(GTK_BOX(vbox), button);

		g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(gtk_widget_destroy), (gpointer)button);
	}

	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show_all(window);

	gtk_main();
	return (0);
}
