#include "gui_util.h"
#include <curl/curl.h>

static size_t write_callback(void *contents,
                             size_t size,
                             size_t nmemb,
                             gpointer user_data) {
    GByteArray *byte_array = (GByteArray *)user_data;
    g_byte_array_append(byte_array, (const guint8 *)contents, size * nmemb);
    return size * nmemb;
}

GdkPixbuf *gdk_pixbuf_new_from_url(const gchar *url) {
    CURL *curl = curl_easy_init();
    GdkPixbuf *pixbuf = NULL;
    GByteArray *byte_array = g_byte_array_new();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, byte_array);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            g_warning("{Utils} Error downloading picture: %s",
                      curl_easy_strerror(res));
        }
        else {
            gsize length = byte_array->len;
            gconstpointer data = byte_array->data;
            GInputStream *input = g_memory_input_stream_new_from_data(data,
                                                                      length,
                                                                      NULL);

            pixbuf = gdk_pixbuf_new_from_stream(input, NULL, NULL);

            g_input_stream_close(input, NULL, NULL);
        }

        curl_easy_cleanup(curl);
    }

    g_byte_array_unref(byte_array);

    return pixbuf;
}
