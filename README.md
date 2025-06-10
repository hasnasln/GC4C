# S-Malloc: Güvenli Bellek Yönetimi Kütüphanesi

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg)

**S-Malloc**, standart `malloc` ve `free` işlevlerine güvenli bir alternatif sunan, C programlama dili için geliştirilmiş özel bir bellek yönetimi kütüphanesidir. Bu kütüphane, ayrılan tüm bellek bloklarını çift yönlü bir bağlı liste üzerinde takip ederek, bellek sızıntılarını önlemeyi ve tüm belleği tek bir komutla güvenli bir şekilde serbest bırakmayı amaçlar.

---

## ✨ Öne Çıkan Özellikler

- **Güvenli Bellek Ayırma**: `malloc` ile ayrılan her bellek alanını otomatik olarak bir bağlı listeye kaydeder.
- **Toplu Bellek Serbest Bırakma**: Program sonunda veya istenilen herhangi bir anda, ayrılmış tüm bellek bloklarını `safe_free_data()` fonksiyonu ile tek seferde serbest bırakma imkanı sunar.
- **Hedefli Serbest Bırakma**: Belirli bir bellek bloğunu, listenin başından (`HEAD_TO_TAIL`) veya sonundan (`TAIL_TO_HEAD`) arayarak serbest bırakabilirsiniz.
- **Kolay Entegrasyon**: Projenize kolayca entegre edilebilir ve `Makefile` ile yönetilebilir.

---

## 🛠️ Derleme ve Kurulum

Projeyi derlemek ve statik kütüphane (`.a`) dosyasını oluşturmak için projenin ana dizininde terminali açın ve aşağıdaki `make` komutlarını kullanın.

1.  **Kütüphaneyi Oluşturma**

    Projenin statik kütüphanesi olan **`libsafemalloc.a`** dosyasını oluşturmak için aşağıdaki komutu çalıştırın:
    ```bash
    make
    ```

2.  **Temizlik**

    - Derleme sırasında oluşan nesne dosyalarını (`.o`) silmek için:
      ```bash
      make clean
      ```
    - Kütüphane dosyası dahil olmak üzere tüm derlenmiş dosyaları silmek için:
      ```bash
      make fclean
      ```

3.  **Yeniden Derleme**

    Projeyi tamamen temizleyip baştan derlemek için:
    ```bash
    make re
    ```

---

## 🚀 Kütüphaneyi Projede Kullanma

`s_malloc` kütüphanesini kendi projenizde kullanmak için aşağıdaki adımları izleyin:

1.  `s_malloc.h` dosyasını projenizin `include` veya ana dizinine, `libsafemalloc.a` dosyasını ise `lib` veya ana dizinine kopyalayın.

2.  Kütüphaneyi kullanacağınız C dosyasına header'ı dahil edin:
    ```c
    #include "s_malloc.h"
    ```

3.  Programınızı derlerken oluşturduğunuz statik kütüphaneye bağlayın.
    Örneğin, `main.c` adında bir dosyanız varsa:
    ```bash
    # -L. -> Kütüphaneyi güncel dizinde ara
    # -lsafemalloc -> 'libsafemalloc.a' kütüphanesini bağla
    cc main.c -L. -lsafemalloc -o program
    ```

### Örnek Kullanım Kodu (`main.c`)

```c
#include "s_malloc.h"
#include <stdio.h>

int main(void)
{
    // 10 adet integer için bellek ayır
    int *my_array = s_malloc(sizeof(int) * 10);
    if (!my_array)
    {
        printf("Bellek ayırma başarısız!\n");
        return (1);
    }

    my_array[0] = 42;
    printf("İlk eleman: %d\n", my_array[0]);

    // Başka bir bellek alanı
    char *message = s_malloc(sizeof(char) * 12);
    if (message)
    {
        // Güvenli string kopyalama
        snprintf(message, 12, "Merhaba!");
        printf("Mesaj: %s\n", message);
    }

    // Program bittiğinde s_malloc ile ayrılmış TÜM belleği tek seferde serbest bırak
    printf("Tüm bellek serbest bırakılıyor...\n");
    safe_free_data();

    return (0);
}
```