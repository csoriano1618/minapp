#include <gtk/gtk.h>
#include <gio/gio.h>

#include "minapp.h"

int
main (int argc, char *argv[])
{
  return g_application_run (G_APPLICATION (min_app_new ()), argc, argv);
}
