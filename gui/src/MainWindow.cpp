

#include "MainWindow.h"

/* GtkWidget is the storage type for widgets */
static GtkWidget *window;
static GtkWidget *button;

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void onHelloPress(GtkWidget *widget, gpointer  data) {
  g_print("Hello World\n");
}

static gboolean onDelete(GtkWidget *widget, GdkEvent  *event, gpointer data) {
  return FALSE;
}

/* Another callback */
static void onDestroy(GtkWidget *widget, gpointer data) {
  gtk_main_quit();
}

// Quit on Q or q
static gboolean onKeyPress(GtkWidget *widget, GdkEventKey *event, gpointer data) {
  if (event->keyval == 81 || event->keyval == 113) {
      g_print("%s pressed, quitting...", gdk_keyval_name(event->keyval));
      gtk_main_quit();
  }
  return TRUE;
}


void MakeWindow() {

  /* This is called in all GTK applications. Arguments are parsed
   * from the command line and are returned to the application. */

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

//  gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

  g_signal_connect(window, "delete-event", G_CALLBACK(onDelete), NULL);

  /* Here we connect the "destroy" event to a signal handler.
   * This event occurs when we call gtk_widget_destroy() on the window,
   * or if we return FALSE in the "delete-event" callback. */
  g_signal_connect(window, "destroy", G_CALLBACK(onDestroy), NULL);

  g_signal_connect(window, "key-press-event", G_CALLBACK(onKeyPress), NULL);

  /* Sets the border width of the window. */
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  /* Creates a new button with the label "Hello World". */
  button = gtk_button_new_with_label("Hello World");

  g_signal_connect(button, "clicked", G_CALLBACK(onHelloPress), NULL);


  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

  gtk_container_add(GTK_CONTAINER(window), button);

}

void ShowWindow() {

  gtk_widget_show(button);

  GdkRectangle *rect;
  GdkDisplay *display = gdk_display_get_default();
  GdkScreen *screen = gdk_display_get_default_screen(display);
  gint width = gdk_screen_get_width(screen);
  gint height = gdk_screen_get_height(screen);

  printf("Screen resolution %i(width) %i(height)\n", width, height);
//  screen->


  gtk_widget_show(window);
  gtk_widget_set_size_request(GTK_WIDGET(window), width, height);
  gtk_widget_activate(window);
//  gtk_window_set_position(GTK_WIDGET(window), 0,0);
}