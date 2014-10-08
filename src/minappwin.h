#ifndef __MINAPPWIN_H
#define __MINAPPWIN_H

#include <gtk/gtk.h>
#include "minapp.h"


#define MIN_APP_WINDOW_TYPE (min_app_window_get_type ())
#define MIN_APP_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MIN_APP_WINDOW_TYPE, MinAppWindow))


typedef struct _MinAppWindow         MinAppWindow;
typedef struct _MinAppWindowClass    MinAppWindowClass;


GType                   min_app_window_get_type     (void);
MinAppWindow       		*min_app_window_new          (MinApp *app);
void                    min_app_window_open         (MinAppWindow *win,
                                                     GFile            *file);


#endif /* __MINAPPWIN_H */
