#include <Arduino.h>
#include <lvgl.h>
#include <esp32_smartdisplay.h>

// Búfer para LVGL
static lv_color_t buf[240 * 10]; // Ajusta el tamaño según la resolución de tu pantalla
auto lv_last_tick = millis();

// Declaración de la imagen (generada por LVGL Image Converter)
extern const lv_img_dsc_t imagen_ejemplo;

// Función para manejar el evento del botón
static void btn_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    // Crea un objeto de imagen y la muestra
    lv_obj_t * img = lv_img_create(lv_scr_act());
    lv_img_set_src(img, &imagen_ejemplo);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
  }
}

void setup() {
  // Inicializa la pantalla
  smartdisplay_init();

  // Inicializa LVGL
  lv_init();

  // Configura el búfer de LVGL
  auto disp = lv_display_get_default();
  lv_display_set_buffers(disp, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

  // Crea un botón
  lv_obj_t * btn = lv_btn_create(lv_scr_act());
  lv_obj_set_size(btn, 100, 50); // Tamaño del botón
  lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0); // Centra el botón
  lv_obj_add_event_cb(btn, btn_event_handler, LV_EVENT_ALL, NULL); // Asigna el manejador de eventos

  // Añade una etiqueta al botón
  lv_obj_t * label = lv_label_create(btn);
  lv_label_set_text(label, "Mostrar Imagen");
  lv_obj_center(label);
}

void loop() {
  auto const now = millis();
  // Actualiza el ticker de LVGL
  lv_tick_inc(now - lv_last_tick);
  lv_last_tick = now;
  // Actualiza la interfaz de LVGL
  lv_timer_handler();
}