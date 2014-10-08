#ifndef __MINAPP_H
#define __MINAPP_H

#include <gtk/gtk.h>


#define MIN_APP_TYPE (min_app_get_type ())
#define MIN_APP(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MIN_APP_TYPE, MinApp))


typedef struct _MinApp       MinApp;
typedef struct _MinAppClass  MinAppClass;


GType       min_app_get_type    (void);
MinApp     *min_app_new         (void);


#endif /* __MINAPP_H */
