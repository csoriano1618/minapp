#include <gtk/gtk.h>
#include <gio/gio.h>

#include "minapp.h"
#include "minappwin.h"

struct _MinApp
{
  GtkApplication parent;
};

struct _MinAppClass
{
  GtkApplicationClass parent_class;
};

G_DEFINE_TYPE(MinApp, min_app, GTK_TYPE_APPLICATION);

static void
min_app_init (MinApp *app)
{

}

static void
quit_activated (GSimpleAction *action,
                GVariant      *parameter,
                gpointer       app)
{
  g_application_quit (G_APPLICATION (app));
}

static GActionEntry app_entries[] =
{
  { "quit", quit_activated, NULL, NULL, NULL }
};

static void
min_app_startup (GApplication *app)
{
  GMenuModel *app_menu;
  const gchar *quit_accels[] = { "<Ctrl>Q", NULL };

  G_APPLICATION_CLASS (min_app_parent_class)->startup (app);

  g_action_map_add_action_entries (G_ACTION_MAP (app),
                                   app_entries, G_N_ELEMENTS (app_entries),
                                   app);

  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "app.quit",
                                         quit_accels);
}

static void
min_app_activate (GApplication *app)
{
  MinAppWindow *win;

  win = min_app_window_new (MIN_APP (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void
min_app_open (GApplication  *app,
              GFile        **files,
              gint           n_files,
              const gchar   *hint)
{
  GList *windows;
  MinAppWindow *win;
  int i;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows)
    win = MIN_APP_WINDOW (windows->data);
  else
    win = min_app_window_new (MIN_APP (app));

  for (i = 0; i < n_files; i++)
    min_app_window_open (win, files[i]);

  gtk_window_present (GTK_WINDOW (win));
}

static void
min_app_class_init (MinAppClass *class)
{
  G_APPLICATION_CLASS (class)->startup = min_app_startup;
  G_APPLICATION_CLASS (class)->activate = min_app_activate;
  G_APPLICATION_CLASS (class)->open = min_app_open;
}

MinApp *
min_app_new (void)
{
  return g_object_new (MIN_APP_TYPE,
                       "application-id", "org.min-app",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}
