#include "minapp.h"
#include "minappwin.h"
#include <gtk/gtk.h>

struct _MinAppWindow
{
  GtkApplicationWindow parent;
};

struct _MinAppWindowClass
{
  GtkApplicationWindowClass parent_class;
};

typedef struct _MinAppWindowPrivate MinAppWindowPrivate;

struct _MinAppWindowPrivate
{
  GtkWidget *toolbar_menu_button;
  GtkWidget *show_label;
};

G_DEFINE_TYPE_WITH_PRIVATE(MinAppWindow, min_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void
show_label_cb (MinAppWindow *win)
{
  MinAppWindowPrivate *priv;
}

static void
min_app_window_append_item (GSimpleAction *action,
                            GVariant      *parameter,
                            gpointer       user_data)
{
  MinAppWindow *window = MIN_APP_WINDOW (user_data);
  g_print("append item\n");
}

static void
min_app_window_remove_item (GSimpleAction *action,
                            GVariant      *parameter,
                            gpointer       user_data)
{
  MinAppWindow *window = MIN_APP_WINDOW (user_data);
  g_print("remove item\n");
}

static void
min_app_window_show_label (GSimpleAction *action,
                           GVariant      *parameter,
                           gpointer       user_data)
{
  MinAppWindow *window = MIN_APP_WINDOW (user_data);
  g_print("show label\n");
}

static GActionEntry win_entries[] = {
  { "append-item", min_app_window_append_item },
  { "remove-item", min_app_window_remove_item },
  { "show-label",  min_app_window_show_label },
  { "main", NULL, "s", "'steak'", NULL }
};  

static void
min_app_window_init (MinAppWindow *win)
{
  MinAppWindowPrivate *priv;
  GtkBuilder *builder;
  GMenuModel *menu;
  GAction *action;

  priv = min_app_window_get_instance_private (win);
  gtk_widget_init_template (GTK_WIDGET (win));

  builder = gtk_builder_new_from_resource ("/org/min-app/toolbar-menu.ui");
  menu = G_MENU_MODEL (gtk_builder_get_object (builder, "menu"));
  gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (priv->toolbar_menu_button), menu);
  g_object_unref (builder);

  g_action_map_add_action_entries (G_ACTION_MAP (win),
                                   win_entries,
                                   G_N_ELEMENTS (win_entries),
                                   win);
}

static void
min_app_window_class_init (MinAppWindowClass *class)
{
  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                               "/org/min-app/window.ui");

  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), MinAppWindow, toolbar_menu_button);
}

MinAppWindow *
min_app_window_new (MinApp *app)
{
  return g_object_new (MIN_APP_WINDOW_TYPE, "application", app, NULL);
}

void
min_app_window_open (MinAppWindow *win,
                     GFile            *file)
{

}
