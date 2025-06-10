# Statik kütüphanenin adı
NAME		= libsafemalloc.a

# C derleyicisi
CC			= cc

# Derleyici bayrakları:
# -Wall -Wextra -Werror: Tüm uyarıları göster ve bunları hata olarak kabul et (temiz kod için)
# -I.: Header dosyalarını güncel dizinde ara (.h dosyası için)
CFLAGS		= -Wall -Wextra -Werror -I.

# Arşivleyici programı ve bayrakları
# r: Dosyaları arşive ekler veya değiştirir
# c: Arşiv yoksa oluşturur
# s: Arşiv için bir indeks oluşturur
AR			= ar rcs

# Kütüphaneyi oluşturacak kaynak dosyalar (.c)
# Eğer başka .c dosyalarınız varsa buraya ekleyin: s_malloc.c dosya2.c dosya3.c
SRCS		= s_malloc.c

# Kaynak dosyalardan üretilecek olan nesne dosyaları (.o)
# .c uzantısını .o ile otomatik olarak değiştirir
OBJS		= $(SRCS:.c=.o)

# Header dosyanız. Değiştiğinde yeniden derleme tetiklenir.
HEADER		= s_malloc.h

# Kural: all
# Varsayılan hedeftir. 'make' komutu çalıştırıldığında bu kural çalışır.
# Amacı kütüphane dosyasını oluşturmaktır.
all:		$(NAME)

# Kural: Kütüphane dosyasını (.a) oluşturma
# Nesne dosyalarına (.o) bağımlıdır.
$(NAME):	$(OBJS)
			@$(AR) $(NAME) $(OBJS)
			@echo "✅ Statik kütüphane '$(NAME)' başarıyla oluşturuldu."

# Kural: Nesne dosyalarını (.o) oluşturma
# Kaynak dosyalarına (.c) ve header dosyasına (.h) bağımlıdır.
%.o:		%.c $(HEADER)
			@$(CC) $(CFLAGS) -c $< -o $@
			@echo "  -> $< derlendi."

# Kural: clean
# Sadece derleme sırasında oluşan nesne dosyalarını (.o) siler.
clean:
			@rm -f $(OBJS)
			@echo "🧹 Nesne dosyaları temizlendi."

# Kural: fclean
# 'clean' kuralını çalıştırır ve ek olarak oluşturulan son kütüphane dosyasını (.a) da siler.
fclean:		clean
			@rm -f $(NAME)
			@echo "🔥 Tüm proje dosyaları temizlendi."

# Kural: re
# Projeyi tamamen temizler ve yeniden derler.
re:			fclean all

# Bu hedeflerin birer dosya adı olmadığını belirtiriz.
.PHONY:		all clean fclean re