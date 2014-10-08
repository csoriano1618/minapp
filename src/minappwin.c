#include "minapp.h"
#include "minappwin.h"
#include <gtk/gtk.h>

struct _MinAppWindowPrivate
{
  GtkWidget *toolbar_menu_button;
  GtkWidget *show_label;
  GMenu     *menu;
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
  MinAppWindow  *window = MIN_APP_WINDOW (user_data);
  GMenuLinkIter *liter;
  GMenuLinkIter *sort_liter;
  GMenuModel    *sort_section;
  GMenuItem     *new_item;
  gchar         *formatted;

  liter = g_menu_model_iterate_item_links (G_MENU_MODEL(window->priv->menu), 1);
  g_menu_link_iter_next (liter);
  sort_section = g_menu_link_iter_get_value (liter);

  new_item = g_menu_item_new ("hi", "win.show-label");
  g_menu_append_item (G_MENU(sort_section), new_item);
}

static void
min_app_window_remove_item (GSimpleAction *action,
                            GVariant      *parameter,
                            gpointer       user_data)
{
  MinAppWindow  *window = MIN_APP_WINDOW (user_data);
  GMenuLinkIter *liter;
  GMenuAttributeIter *sort_liter;
  GMenuModel    *sort_section;
  const gchar         *attr_name;
  const gchar         *attr_value;
  gint           n_items;

  liter = g_menu_model_iterate_item_links (G_MENU_MODEL(window->priv->menu), 1);
  g_menu_link_iter_next (liter);
  sort_section = g_menu_link_iter_get_value (liter);
  n_items = g_menu_model_get_n_items (sort_section);
  sort_liter = g_menu_model_iterate_item_attributes (sort_section, n_items - 1);


  while (g_menu_attribute_iter_next (sort_liter))
  {
    attr_name = g_menu_attribute_iter_get_name (sort_liter);
    if (strcmp(attr_name, "label") == 0)
    {
      attr_value = g_variant_print(g_menu_attribute_iter_get_value (sort_liter), FALSE);
      if (strcmp(attr_value, "'hi'") == 0)
      {
        g_menu_remove (G_MENU(sort_section), n_items - 1);
        break;
      }
    }
  }
}

static void
min_app_window_show_label (GSimpleAction *action,
                           GVariant      *parameter,
                           gpointer       user_data)
{
  MinAppWindow *window = MIN_APP_WINDOW (user_data);
  g_print("show label\n");
}

static void
min_app_window_sort_order_changed (GSimpleAction *action,
                                   GVariant      *value,
                                   gpointer       user_data)
{
  //MinAppWindow *window = MIN_APP_WINDOW (user_data);
  g_print ("short order changed %s\n", g_variant_print(value, FALSE));

  g_simple_action_set_state (action, value);
}

static GActionEntry win_entries[] = {
  { "append-item", min_app_window_append_item },
  { "remove-item", min_app_window_remove_item },
  { "show-label",  min_app_window_show_label },
  { "sort", NULL, "s", "'sort_by_name'", min_app_window_sort_order_changed }
};  

static void
min_app_window_init (MinAppWindow *win)
{
  MinAppWindowPrivate *priv;
  GtkBuilder *builder;
  GMenuModel *menu;
  GAction *action;

  win->priv = min_app_window_get_instance_private (win);
  priv = min_app_window_get_instance_private (win);
  g_print("here\n");
  gtk_widget_init_template (GTK_WIDGET (win));
  g_print("here after\n");

  builder = gtk_builder_new_from_resource ("/org/min-app/toolbar-menu.ui");
  win->priv->menu = G_MENU (gtk_builder_get_object (builder, "menu"));
  gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (priv->toolbar_menu_button), G_MENU_MODEL (win->priv->menu));
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
