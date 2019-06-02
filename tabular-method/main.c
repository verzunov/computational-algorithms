#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# include <gtk/gtk.h>
#define EPS 1.0e-8
double  P[9], x, x0, x9, h;
int N,K;
double bessel(double x)
{
    double R, S, T;
    int N;
    R=x/2; T=1.0; N=round(P[1]);
    for(K=0; K<N; K++) T*=R/K;
    K=1; S=T;
    if (abs(R)> EPS)
    {
        R*=-R;
        while(abs(T)>P[2])
        {
            T*=R/(K*(K+N));
            S+=T; K++;
        }
    }
    return S;
}
int main(int argc, char *argv[])
{
  	/* Объявляем виджеты */
	GtkWidget *label;	/* Метка*/
	GtkWidget *window;	/*Главное окно*/
    GtkWidget* grid; /*Контейнер*/
    GtkWidget *viewX0; /*Поле ввода для X0*/
    GtkTextBuffer *bufferX0; /*Текстовый буфер для X0*/

	/* Инициализируем GTK+ */
	gtk_init(&argc, &argv);
	/* Создаем главное окно */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    /* Создаем контейнер */
    grid = gtk_grid_new ();
	/* Добавляем контейнер в окно*/
    gtk_container_add(GTK_CONTAINER(window), grid);
	/* Устанавливаем заголовок окна и рамки */
	gtk_window_set_title(GTK_WINDOW(window), "Табличный метод");
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	/* Создаем метку с текстом "X0" */
	label = gtk_label_new("X0:");
	/* Вставляем метку в контейнер */
    gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);
    /*Создаем поле ввода и текстовый буфер для X0*/
    viewX0 = gtk_text_view_new ();
    bufferX0 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (viewX0));
    /* Вставляем поле в контейнер */
    gtk_grid_attach (GTK_GRID (grid), viewX0, 1, 0, 1, 1);
	/* Показываем окно вместе с виджетами */
	gtk_widget_show_all(window);
	/* Соединяем сигнал завершения с выходом из программы */
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	/* Приложение переходит в вечный цикл ожидания действий пользователя */
	gtk_main();
	return 0;
}
