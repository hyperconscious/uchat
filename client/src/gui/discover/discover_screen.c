#include "requests.h"

void on_discover_screen_show(void) {
    const int column_count = 4;
    const int row_count = 4;

    uint16_t count = 0;
    Person *founded_chats = rq_discover(user_id,
                            &count, serverAddress, Port);
   
 

    
    //DiscoverPerson person = {.id = 0, .name = "Paul", .image_url = NULL};
    GtkGrid *discover_grid = GTK_GRID(get_widget(DISCOVER_GRID_ID));
    int j = 0;
      int counter = 0;
    for (int i = 0; i < row_count && counter < count; i++) {
      if (founded_chats[counter].id == user_id)
      {
        counter++;
        
      }
      
            founded_chats[counter].image_url = NULL;
            GtkWidget *discover_grid_item =
                    create_discover_grid_item(founded_chats[counter].name, founded_chats[counter].image_url);
                   

            gtk_grid_attach(discover_grid, discover_grid_item, i, j, 1, 1);
        if (i == column_count - 1) {
            i = -1;
            j++;

        }
        counter++;
    }

    free(founded_chats);

}
