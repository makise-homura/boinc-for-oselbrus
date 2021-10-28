BOINC - популярная инфраструктура community-based научных расчётов, в которую входят проекты различных научных организаций и институтов.
Для нас возможность запускать проекты BOINC интересна тем, что они представляют собой хороший образец тестирования гетерогенных расчётных задач на платформе "Эльбрус"; в частности, были обнаружены несколько проблем с бинарным транслятором rtc и компилятором.

В данном файле встречаются ссылки на внутренние ресурсы МЦСТ (например, на bugzilla и wiki) и имена хостов из внутренней сети МЦСТ; для пользователей, не имеющих туда доступа, эти ссылки работать не будут. Однако, общее понимание возможно и без учёта информации, расположенной по этим ссылкам.

## Способы работы BOINC

Имеется возможность запуска BOINC на Эльбрусе как в **транслируемом** с помощью бинарного компилятора уровня приложений (rtc) режиме (что позволит выполнять задачи, собранные под архитектуру x86_64 - таково подавляющее большинство существующих задач), так и в **нативном** (но для этого необходимо будет вручную собрать каждую выполняемую задачу), если проект поддерживает выполнение в режиме [анонимной платформы](https://boinc.berkeley.edu/wiki/Anonymous_platform).

В [стенде сектора разработки вычислительных модулей](http://wiki.lab.sun.mcst.ru/e2kwiki/Стенд_сектора_разработки_вычислительных_модулей) под эксперименты с BOINC во внутренней сети МЦСТ выделено 4 машины:
* **suika** - 1 × i5-7600K, Ubuntu 20.04: контрольная машина (развёрнут, работает); служит для проверки работоспособности задач под Linux в целом и сравнения с "Эльбрусом";
* **kisume** - 4 × E8C, ОС Эльбрус 6.0 (транслируемая 6.0): транслируемый BOINC (развёрнут, работает);
* **koishi** - 1 × E8C, ОС Эльбрус 4.0 (транслируемая 6.0): транслируемый BOINC (развёрнут, работает); служит для подтверждения работоспособности задач на 1-процессорных машинах в случае неработоспособности на 4-процессорных;
* **minoriko** - 4 × E8C2, ОС Эльбрус 6.0 (транслируемая 6.0): транслируемый BOINC (развёрнут, работает).

## Используемые проекты

На данный момент осуществляется тестирование и набор статистики выполнения на следующих проектах:

* **[Asteroids@home](http://asteroidsathome.net/boinc/)**

На октябрь 2021 года находится в оффлайне.

* **[Cosmology@Home](http://www.cosmologyathome.org/)**

Работает.

* **[Einstein@Home](http://einstein.phys.uwm.edu/)**

Работает, в том числе задача Binary Radio Pulsar Search - нативно.

* **[LHC@Home](https://lhcathome.cern.ch/lhcathome/)**

Работает.

* **[MilkyWay@home](http://milkyway.cs.rpi.edu/milkyway/)**

Работает, в том числе задача N-Body Simulation - нативно.

* **[RakeSearch](http://rake.boincfast.ru/rakesearch/)**

На данный момент поиск в проекте завершён, задачи не рассылаются, возможно, проект будет закрыт. За время участия в этом проекте получены некоторые [данные по производительности, опубликованные автором проекта](https://pikabu.ru/story/russkiy_protsessor_yelbrus_v_raspredelennyikh_vyichisleniyakh_na_blago_nauki_7179570), а также собрано нативное приложение (см. [форум](https://boinc.ru/forum/topic/novosti-proekta-rakesearch/?part=3)).

* **[Universe@Home](https://universeathome.pl/universe/)**

Работает.

Принимаются предложения по добавлению других проектов.

## Установка BOINC

### Установка на контрольной машине

На контрольной машине установлены следующие пакеты из репозитория Ubuntu 20.04:
```
boinc             7.16.6+dfsg-1   all  
boinc-client      7.16.6+dfsg-1   amd64
boinc-manager     7.16.6+dfsg-1   amd64
boinctui          2.5.0-1build2   amd64
libboinc7:amd64   7.16.6+dfsg-1   amd64
```
Установки этих пакетов и первоначальной настройки достаточно для запуска BOINC на x86_64.

### Окружение для работы в транслируемом режиме

Можно использовать любой образ файловой системы для архитектуры x86_64, но для чистоты эксперимента используется образ ОС Эльбрус.

Для простоты установки сделан пакет с образом файловой системы, который можно сразу установить в систему (сам пакет весит 8,5 ГБ, на диске занимает около 40 ГБ в `/opt/mcst/`, время распаковки - примерно 40 минут) командой:
```
dpkg -i /net/satori/i-data/9a03a6a1/nfs/shared/rtc_packages/os-elbrus-image-x86-64-6.0-rc3_6.0.3-u1_all.deb
```
Сетевой ресурс `/net/satori` доступен из внутренней сети МЦСТ при включённой AutoFS.

* Ставим образ файловой системы ОС Эльбрус 6.0:
```
dpkg -i /net/satori/i-data/9a03a6a1/nfs/shared/rtc_packages/os-elbrus-image-x86-64-6.0-rc3_6.0.3-u1_all.deb
```
* Потом файл `/etc/resolv.conf` нужно скопировать в каталог `/opt/mcst/os_elbrus.6.0-rc3.x86_64`, чтобы транслируемой ОС был доступен DNS.

### Установка в транслируемом режиме

Возможны несколько вариантов в зависимости от образа гостевой ОС бинарного транслятора:

* Просто распаковать или установить пакеты из той же Ubuntu, разумеется, доставив все нужные зависимости (если используется ОС, в репозитории пакетов которой есть BOINC);
* Скачать нужный скрипт установки [отсюда](https://boinc.berkeley.edu/download_all.php) и попытаться установить всё автоматически;
* Просто собрать BOINC из исходников.

Разумеется, это всё нужно делать из-под бинарного транслятора, запустив его командой типа такой:
```
/opt/mcst/rtc/bin/rtc_opt_rel_p1_x64_ob --path_prefix /opt/mcst/os_elbrus.6.0-rc3.x86_64 -- /bin/bash
```
### Сборка BOINC

Для сборки необходима версия ОС Эльбрус 6.0-rc3 или более поздняя.

Особенности сборки:
* Можно при сборке BOINC указать параметр конфигурации `--disable-server`, если мы не хотим собирать сервер (а обычно мы не хотим);
* Необходимо указать правильный путь к wxWidgets 3.0 при сборке (это нужно для сборки графического менеджера). Для ОС Эльбрус это `/usr/lib/wx/config/x86_64-linux-gnu-gtk2-unicode-3.0` или `/usr/lib/wx/config/e2k-mcst-linux-gnu-gtk2-unicode-3.0` в зависимости от архитектуры.

Собственно, сборка (для версии 7.18.1):
```
git clone https://github.com/BOINC/boinc 
cd boinc 
git checkout client_release/7.18/7.18.1
./_autosetup
./configure -C --disable-server --prefix=/usr --with-wx-config=/usr/lib/wx/config/e2k-mcst-linux-gnu-gtk2-unicode-3.0
make -j32
make install
```
Если сборка во много потоков под транслятором зависает, то помогает собирать в один поток.

### Настройка прокси

Чтобы клиент BOINC мог получать задания с сервера через прокси МЦСТ, в файле `сс_config.xml` в рабочем каталоге клиента (обычно `/var/lib/boinc_client`) должен быть следующий параметр (если соответствующая группа параметров уже существует, надо добавлять в неё, а не создавать новую):
```
<cc_config>
  <options>
    <proxy_info>
      <http_server_name>labproxy1.sun.mcst.ru</http_server_name>
      <http_server_port>8080</http_server_port>
    </proxy_info>
  </options>
</cc_config>
```
## Управление BOINC

Инфраструктура BOINC состоит из сервера (выдающего расчётные задачи), клиента (выполняющего расчёты) и менеджера (программы управления клиентом). Чаще всего клиент и менеджер располагаются на одной машине, но в целом это не обязательно. Организация же сервера в нашем случае не рассматривается.

Опробованы три менеджера: командной строки **boinccmd**, текстовый **boinctui** и графический **boincmgr**. Первый и последний входят в комплект ПО BOINC, второй является отдельной программой.

Менеджеры BOINC не имеет смысла запускать через бинарный транслятор (хоть и можно, в принципе). Нативный менеджер прекрасно работает с транслируемым клиентом (и, разумеется, с нативным).

### Сборка менеджеров

Менеджеры **boinccmd** и **boincmgr** собираются в процессе сборки нативного BOINC. Если нас не интересует при этом нативный клиент BOINC (например, мы будем запускать клиент на другой машине или через транслятор), то конфигуратору сборки можно указать опцию `--disable-client` (и `--disable-server`, если нужно).

Сборка **boinctui** 2.5.1:
```
wget https://github.com/suleman1971/boinctui/archive/dbed88da21f2c74f4982467ac683d99019837265.zip -O boinctui.zip
unzip boinctui.zip
cd boinctui-dbed88da21f2c74f4982467ac683d99019837265
autoreconf -f -i
./configure --prefix=/usr --without-gnutls
make -j32
make install
```
Вместо **boinctui** можно использовать его более развитую версию - **boinctui-extended** (например, последний на момент октября 2021 коммит `1725f33`):
```
git clone https://github.com/mpentler/boinctui-extended
cd boinctui-extended
git checkout 1725f33
autoconf
./configure --prefix=/usr --without-gnutls
make -j32
make install
```
Запуск менеджеров производится очевидными командами `boinccmd`, `boincmgr`, `boinctui` и `boinctui-extended`.

Если **boinctui** или **boinctui-extended** рисуют рамки текстовыми символами, а не псевдографикой, их можно запускать с переменной окружения `TERM=putty`.

### Настройка доступа к клиенту

Доступ менеджера к клиенту настраивается с помощью файлов в рабочем каталоге клиента (обычно `/var/lib/boinc_client`):

* `gui_rpc_auth.cfg` - пароль, который должен передать менеджер клиенту;
* `remote_hosts.cfg` - хосты (IP или hostname), с которых менеджер может обращаться к клиенту (по одному в строке).

Если первый файл не существует, он будет создан, и в него будет записан сгенерированный пароль. Пустым этот файл на новых версиях BOINC быть не может.

Если второй файл не существует, то доступ будет возможен с любого хоста (разумеется, если это разрешено нижеследующей опцией).

Чтобы разрешить доступ к клиенту BOINC с других машин, нужно сделать одну из этих вещёй:
* Добавить опцию `<allow_remote_gui_rpc>1</allow_remote_gui_rpc>` в блок `<options>` файла `сс_config.xml`;
* Или в командную строку запуска добавить параметр `--allow_remote_gui_rpc`.

### Работа с командным менеджером

Командами `boinccmd --help` или `man boinccmd` можно получить справку по использованию командного менеджера. Большинство операций удобно производить через другие менеджеры, за исключением вывода сообщений, статистики и т.п. - для них менеджер командной строки подходит всеьма хорошо.

Часто используемые команды:
* `--host хост` и `--passwd пароль` - добавить в командную строку, если обращаемся к удалённому клиенту (хост - хостнейм или IP удалённого компьютера, пароль - содержимое `gui_rpc_auth.cfg` в рабочем каталоге клиента).
* `--client_version` - посмотреть версию клиента (не менеджера!)
* `--get_daily_xfer_history` - посмотреть, сколько байт передано и принято за все дни работы клиента
* `--get_disk_usage` - посмотреть, сколько выделено и занято проектами на диске
* `--get_file_transfers` - посмотреть лог передач
* `--get_messages` - посмотреть лог сообщений
* `--get_simple_gui_info` - посмотреть проекты и задачи
* `--get_state` - посмотреть состояние
* `--get_tasks` - посмотреть задачи
* `--network_available` - передать непереданные из-за проблем с сетью задачи
* `--quit` - завершить работу клиента
* `--read_cc_config` - перечитать конфигурацию (при этом возможен отвал подключенных менеджеров типа boinctui, их надо будет просто перезапустить)

Если параметр `--passwd` не задан, то пароль читается из файла `gui_rpc_auth.cfg` в текущем каталоге. Поэтому локально менеджер для выполнения операций, требующих пароля, следует запускать из рабочего каталога клиента. То же относится и к графическому менеджеру.

### Работа с текстовым менеджером

Менеджер запускается командой `boinctui`.

Если хосты не настроены, он сразу выдаст окошко списка хостов, в который нужно внести те хосты, за которыми будет следить менеджер.

Клавишей Ins можно добавить, если нужно, дополнительные строчки. Порт менять в общем случае не нужно, в поле хоста надо вписать имя хоста, где работает клиент (`127.0.0.1` или `localhost` - для локального клиента), в поле пароля - содержимое `gui_rpc_auth.cfg` в рабочем каталоге клиента.

Основные клавиши управления:
* F9 - войти в меню
* N - переключение между хостами
* С - отредактировать список хостов
* Стрелки - выбрать какое-либо задание, Enter - посмотреть его характеристики (закрыть окно по ESC-ESC)
* Q - выход

Цветовая кодировка:
* Цвет строчек задач: зелёный - получаемые с сервера, серый - готовые к выполнению, жёлтый - выполняемые, белый - приостановленные, синий - выдающие результаты на сервер, тёмно-серые - завершённые.
* Цвет процентов выполнения: розовый - задача может использовать GPU (но не обязательно использует).
* Цвет состояния задачи: красный - задача завершилась с ошибкой.
* Цвет оставшегося времени до выполнения проекта (est): красный - осталось совсем чуть-чуть (или нисколько).
* Цвет оставшегося времени до дедлайна (d/l): синий - опасная бизость к дедлайну (при аплоаде задачи после дедлайна сервер имеет право её не принять).

В текстовом менеджере удобно использовать шрифт маленького размера (особенно на мониторах с небольшим разрешением, например, шрифт 6x10 вместо стандартного 8x16).

Перед использованием его надо скопировать в `/usr/share/consolefonts/`:
```
wget https://github.com/makise-homura/boinc-for-oselbrus/raw/master/6x10.psf -O /usr/share/consolefonts/6x10.psf
```
Установка шрифта на физической консоли (здесь для примера `tty0`; без параметра `-C` шрифт будет установлен на текущей консоли):
```
setfont -C /dev/tty0 6x10.psf
```
### Автоматическая загрузка при старте ОС

На ОС Эльбрус нужно создать init-скрипт `/etc/init.d/boinc_service` (см. [репозиторий](https://github.com/makise-homura/boinc-for-oselbrus); ему может потребоваться скрипт `cgroupfs-mount` в случае, описанном в главе "Настройка cgroupfs").
```
wget https://raw.githubusercontent.com/makise-homura/boinc-for-oselbrus/master/boinc_service -O /etc/init.d/boinc_service && chmod 755 /etc/init.d/boinc_service
```
Важно: имя скрипта не должно совпадать с именем бинарника клиента BOINC.

После этого нужно его включить командой `chkconfig boinc_service on`.

Кроме этого, при наличии данного скрипта можно управлять клиентом BOINC с помощью параметров скрипта:
* `service boinc_service start` - запустить клиент;
* `service boinc_service stop` - остановить клиент;
* `service boinc_service status` - узнать, запущен ли клиент;
* `service boinc_service restart` - перезапустить клиент;
* `service boinc_service reload` - перезагрузить конфигурацию (`cc_config.xml`).

Этот скрипт позволяет корректно работать как с нативным, так и с транслируемым BOINC. Разумеется, если включать его загрузку при старте ОС, то CernVM-FS (если используется) должна также монтироваться при запуске ОС.

## Работа в режиме бинарной трансляции

Если скрипт `boinc_service` не используется, то в общем случае boinc запускается командой:
```
/opt/mcst/rtc/bin/rtc_opt_rel_p1_x64_ob --path_prefix /opt/mcst/os_elbrus.6.0-rc3.x86_64 /usr/bin/boinc --daemon --dir /var/lib/boinc
```
Рекомендуется использовать бинарный транслятор rtc версии не ниже 4.0 и образ файловой системы ОС Эльбрус не ниже 6.0-rc3 (в противном случае некоторые задачи могут не работать или завершаться с ошибкой; на старых версиях rtc и ОС такое было с задачами Einstein@home и Universe@home).

Здесь и далее все пути даны по умолчанию:
* `/opt/mcst/rtc/bin/rtc_opt_rel_p1_x64_ob` - путь к бинарному транслятору (для случая хоста на основе Эльбрус-8С);
* `/opt/mcst/os_elbrus.6.0-rc3.x86_64` - путь к образу гостевой системы;
* `/usr/bin/boinc` - путь к бинарнику BOINC внутри образа гостевой системы;
* `/var/lib/boinc` - путь к рабочему каталогу BOINC внутри образа гостевой системы.

Следует иметь в виду, что из-за [bug 116902](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=116902) может потребоваться в некоторых случаях [выключать ASLR](https://askubuntu.com/questions/318315/how-can-i-temporarily-disable-aslr-address-space-layout-randomization) в хостовой ОС при работе rtc. Это можно сделать временно, командой `echo 0 > /proc/sys/kernel/randomize_va_space` (если ASLR во включённом состоянии, то в этом файле находится число 2); или сделать это постоянно, добавив в `/etc/sysctl.conf` строчку `kernel.randomize_va_space = 0`.

Если скрипт `boinc_service` не используется, то "красиво" (gracefully) завершить работу клиента можно, дав команду `boinccmd --quit` из рабочего каталога клиента.

### Особенности работы с проектами LHC@Home

По очевидным причинам (отсутствие аппаратной виртуализации) приложения LHC@home, требующие VirtualBox, запускать на "Эльбрусе" невозможно. Такими приложениями являются:
* ATLAS Simulation / vbox64_mt_mcore_atlas
* CMS Simulation / vbox64
* Theory Simulation / vbox64_theory

Однако, можно запускать аналоги этих приложений нативно. Это:
* ATLAS Simulation / native_mt
* Theory Native / native_theory
* ATLAS (long simulation) / long_native_mt

Кроме того, есть ещё приложения SixTrack и sixtracktest, которым контейнеры или виртуализация не нужны.

Для обоих упомянутых придожений (далее просто ATLAS и Theory) нужны определённые зависимости:
* ATLAS: cvmfs, singularity;
* Theory: cvmfs, libseccomp, ядро с поддержкой namespaces (например, 4.9.0-3.5-e8c - достаточно), cgroupfs, USER namespaces.

На данный момент (октябрь 2021) запуск и ATLAS, и Theory блокирован [bug 116955](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=116955).

#### Установка и использование cvmfs

CernVM-FS (cvmfs) - пакет монтирования удалённых файловых систем, разработанный CERN и использующийся в данном случае для доступа к образам и средствам работы с контейнерами, в которые оформлены программы расчётов, использующиеся в CERN, в том числе для инфраструктуры BOINC, а именно ATLAS, CMS и Theory.

Немного информации по установке: [тут](https://cvmfs.readthedocs.io/en/stable/cpt-quickstart.html) и [тут](https://lhcathome.cern.ch/lhcathome/forum_thread.php?id=4971#38259).

Особенности сборки:
* Используем версию 2.5.2.
* В архиве `externals/protobuf/protobuf-2.6.1.tar.bz2` надо заменить файлы `config.guess`, `config.sub`, `gtest/build-aux/config.guess`, `gtest/build-aux/config.sub` на аналоги из поставки ОС Эльбрус (лежат в каталоге `/usr/share/automake-1.16` или подобном);
* К файлу `externals/sqlite3/src/sqlite3.c` надо прикладывать [патч](https://raw.githubusercontent.com/makise-homura/boinc-for-oselbrus/master/sqlite-builtin.patch) (до появления lcc-1.24, см. [bug 95334](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=95334)).

Последовательность сборки с учётом этого:
```
wget https://github.com/cvmfs/cvmfs/archive/cvmfs-2.5.2.tar.gz
tar xf cvmfs-2.5.2.tar.gz
cd cvmfs-cvmfs-2.5.2
pushd externals/protobuf
tar xf protobuf-2.6.1.tar.bz2
cp /usr/share/automake-1.16/config.* protobuf-2.6.1/
cp /usr/share/automake-1.16/config.* protobuf-2.6.1/gtest/build-aux/
rm protobuf-2.6.1.tar.bz2
tar cjf protobuf-2.6.1.tar.bz2 protobuf-2.6.1/
popd
wget https://raw.githubusercontent.com/makise-homura/boinc-for-oselbrus/master/sqlite-builtin.patch
patch -p1 < sqlite-builtin.patch
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_LIBCVMFS_CACHE=OFF -DBUILD_SERVER=OFF ..
make -j16
make install
```
* Сборку также нужно повторить и под бинарным транслятором, если мы работаем в транслируемом режиме.

Иногда при сборке под транслятором может возникать ошибка:
```
configureHook.sh: ./configure: /bin/sh: неверный интерпретатор: Отказано в доступе
```
Чтобы её избежать, нужно в файле `externals/protobuf/src/configureHook.sh` заменить вызов `./configure` на `/bin/sh ./configure`.

Если сборка во много потоков под транслятором зависает, то помогает собирать в один поток.

Нативная сборка удачно проходит под ОС Эльбрус 4.0-rc5 + lcc 1.23.19, но ломается под 6.0-rc3 + lcc 1.25.09 (см. [bug 129046](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=129046)). Если сборка отваливается, то нужно к каталогу сборки CVMFS применить [патч](https://github.com/makise-homura/boinc-for-oselbrus/raw/master/cvmfs-129046.patch) командой типа `patch -p1 < cvmfs-129046.patch`.

После завершения сборки и установки в хостовой ОС (и в транслируемой, если там тоже была повторена сборка) имеется набор ПО для поддержки cvmfs.

Теперь необходимо настроить нативную cvmfs:

* Добавляем пользователя (в хостовой ОС):
```
useradd cvmfs -d /var/lib/cvmfs -m
```
В гостевой ОС также можно добавить пользователя. Во избежание проблем стоит добавлять его с тем же UID, что и в хостовой ОС.

* Устанавливаем прокси (в хостовой и гостевой ОС):
```
echo 'CVMFS_HTTP_PROXY="http://labproxy1.sun.mcst.ru:8080"' >> /etc/cvmfs/default.conf
```
* Создаём точки монтирования (только в хостовой ОС):
```
for i in atlas.cern.ch atlas-condb.cern.ch grid.cern.ch sft.cern.ch cernvm-prod.cern.ch alice.cern.ch; do mkdir -p /cvmfs/$i ; done
```
* В файл `/etc/fstab` добавляем строчки (только в хостовой ОС):
```
atlas.cern.ch           /cvmfs/atlas.cern.ch            cvmfs   defaults        0 0
atlas-condb.cern.ch     /cvmfs/atlas-condb.cern.ch      cvmfs   defaults        0 0
cernvm-prod.cern.ch     /cvmfs/cernvm-prod.cern.ch      cvmfs   defaults        0 0
grid.cern.ch            /cvmfs/grid.cern.ch             cvmfs   defaults        0 0
sft.cern.ch             /cvmfs/sft.cern.ch              cvmfs   defaults        0 0
alice.cern.ch           /cvmfs/alice.cern.ch            cvmfs   defaults        0 0
```
На Эльбрусе модуль fuse надо добавить в список загружаемых модулей (`` /etc/modules-`uname -r` ``) хостовой ОС.

Чтобы CVMFS заработала без перезагрузки, надо выполнить следующие команды (под хостовой ОС):
```
modprobe fuse; mount -a
```
При этом BOINC надо запускать, прокидывая средствами бинарного транслятора (ключ `-b`) каталог `/cvmfs`, а также (см. [bug 117861](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=117861)) файлы `/etc/fstab` и `/etc/mtab` в гостевую ОС:
```
/opt/mcst/rtc/bin/rtc_opt_rel_p1_x64_ob --path_prefix /opt/mcst/os_elbrus.4.0-rc4.x86_64 -b /cvmfs -b /etc/fstab -b /etc/mtab -- /usr/bin/boinc --daemon --dir /var/lib/boinc
```
Скрипт `boinc_service`, приведённый выше, так и делает.

Полезные настройки cvmfs можно посмотреть [здесь](https://twiki.cern.ch/twiki/bin/view/AtlasComputing/Cvmfs21) и [здесь](https://cvmfs.readthedocs.io/en/stable/cpt-configure.html).

#### Настройка cgroupfs

Подсистема cgroupfs используется в контейнерах, запускаемых с помощью runc.

Для монтирования и проверки работоспособности используются два скрипта: 
* Монтирование: [cgroupfs-mount](https://raw.githubusercontent.com/tianon/cgroupfs-mount/master/cgroupfs-mount)
* Проверка: [check-config.sh](https://raw.githubusercontent.com/opencontainers/runc/master/script/check-config.sh)

При проверке важно обращать внимание на следующие строчки:
```
Generally Necessary:
- cgroup hierarchy: properly mounted [/sys/fs/cgroup]
- CONFIG_NAMESPACES: enabled
Optional Features:
- CONFIG_USER_NS: enabled
```
Если они такие, то всё должно быть нормально.

Если эти скрипты положить в `/root/` внутри образа гостевой ОС, то скрипт `boinc_service`, приведённый выше, подцепит их.

#### Сборка libseccomp (нужно только в транслируемой ОС)

Актуально для старых дистрибутивов. В дистрибутивах ветки 6.0 libseccomp уже есть.

Из-под бинарного транслятора делаем:
```
git clone https://github.com/seccomp/libseccomp
cd libseccomp
./autogen.sh
./configure --prefix=/usr
make -j16
make install
ln -s /usr/lib/libseccomp.so.0 /usr/lib/libseccomp.so.2
```
#### Особенности работы с singularity

[Singularity](http://singularity.lbl.gov/admin-guide) - одно из решений контейнеризации приложений, которое использует CERN для своих расчётов.

Без singularity нативный ATLAS выпадает с ошибкой:
```
<core_client_version>7.15.0</core_client_version>
<![CDATA[
<message>
process exited with code 195 (0xc3, -61)</message>
<stderr_txt>
18:40:44 (30913): wrapper (7.7.26015): starting
18:40:44 (30913): wrapper: running run_atlas (--nthreads 12)
singularity image is /cvmfs/atlas.cern.ch/repo/containers/images/singularity/x86_64-slc6.img
sys.argv = ['/var/lib/boinc-client/slots/39/run_atlas', '--nthreads', '12']
THREADS=12
Checking for CVMFS
CVMFS is installed
OS:cat: /etc/redhat-release: &#208;&#157;&#208;&#181;&#209;&#130; &#209;&#130;&#208;&#176;&#208;&#186;&#208;&#190;&#208;&#179;&#208;&#190; &#209;&#132;&#208;&#176;&#208;&#185;&#208;&#187;&#208;&#176; &#208;&#184;&#208;&#187;&#208;&#184; &#208;&#186;&#208;&#176;&#209;&#130;&#208;&#176;&#208;&#187;&#208;&#190;&#208;&#179;&#208;&#176;

This is not SLC6, need to run with Singularity....
Checking Singularity...
sh: singularity: &#208;&#186;&#208;&#190;&#208;&#188;&#208;&#176;&#208;&#189;&#208;&#180;&#208;&#176; &#208;&#189;&#208;&#181; &#208;&#189;&#208;&#176;&#208;&#185;&#208;&#180;&#208;&#181;&#208;&#189;&#208;&#176;
Singularity is not installed, aborting

running start_atlas return value is 2
tar cvf shared/result.tar.gz 
tar: &#208;&#160;&#208;&#190;&#208;&#177;&#208;&#186;&#208;&#184;&#208;&#185; &#208;&#190;&#209;&#130;&#208;&#186;&#208;&#176;&#208;&#183; &#208;&#190;&#209;&#130; &#209;&#129;&#208;&#190;&#208;&#183;&#208;&#180;&#208;&#176;&#208;&#189;&#208;&#184;&#209;&#143; &#208;&#191;&#209;&#131;&#209;&#129;&#209;&#130;&#208;&#190;&#208;&#179;&#208;&#190; &#208;&#176;&#209;&#128;&#209;&#133;&#208;&#184;&#208;&#178;&#208;&#176;
&#208;&#159;&#208;&#190;&#208;&#191;&#209;&#128;&#208;&#190;&#208;&#177;&#209;&#131;&#208;&#185;&#209;&#130;&#208;&#181; &#194;&#171;tar --help&#194;&#187; &#208;&#184;&#208;&#187;&#208;&#184; &#194;&#171;tar --usage&#194;&#187; &#208;&#180;&#208;&#187;&#209;&#143;
&#208;&#191;&#208;&#190;&#208;&#187;&#209;&#131;&#209;&#135;&#208;&#181;&#208;&#189;&#208;&#184;&#209;&#143; &#208;&#177;&#208;&#190;&#208;&#187;&#208;&#181;&#208;&#181; &#208;&#191;&#208;&#190;&#208;&#180;&#209;&#128;&#208;&#190;&#208;&#177;&#208;&#189;&#208;&#190;&#208;&#179;&#208;&#190; &#208;&#190;&#208;&#191;&#208;&#184;&#209;&#129;&#208;&#176;&#208;&#189;&#208;&#184;&#209;&#143;.

*****************The last 100 lines of the pilot log******************
tail: &#208;&#189;&#208;&#181;&#208;&#178;&#208;&#190;&#208;&#183;&#208;&#188;&#208;&#190;&#208;&#182;&#208;&#189;&#208;&#190; &#208;&#190;&#209;&#130;&#208;&#186;&#209;&#128;&#209;&#139;&#209;&#130;&#209;&#140; &#194;&#171;pilotlog.txt&#194;&#187; &#208;&#180;&#208;&#187;&#209;&#143; &#209;&#135;&#209;&#130;&#208;&#181;&#208;&#189;&#208;&#184;&#209;&#143;: &#208;&#157;&#208;&#181;&#209;&#130; &#209;&#130;&#208;&#176;&#208;&#186;&#208;&#190;&#208;&#179;&#208;&#190; &#209;&#132;&#208;&#176;&#208;&#185;&#208;&#187;&#208;&#176; &#208;&#184;&#208;&#187;&#208;&#184; &#208;&#186;&#208;&#176;&#209;&#130;&#208;&#176;&#208;&#187;&#208;&#190;&#208;&#179;&#208;&#176;
***************diag file************
cat: *.diag: &#208;&#157;&#208;&#181;&#209;&#130; &#209;&#130;&#208;&#176;&#208;&#186;&#208;&#190;&#208;&#179;&#208;&#190; &#209;&#132;&#208;&#176;&#208;&#185;&#208;&#187;&#208;&#176; &#208;&#184;&#208;&#187;&#208;&#184; &#208;&#186;&#208;&#176;&#209;&#130;&#208;&#176;&#208;&#187;&#208;&#190;&#208;&#179;&#208;&#176;
******************************WorkDir***********************
&#208;&#184;&#209;&#130;&#208;&#190;&#208;&#179;&#208;&#190; 52
drwxrwx--x  3 root root 4096 &#208;&#188;&#208;&#176;&#208;&#185; 23 18:40 .
drwxrwx--x 47 root root 4096 &#208;&#188;&#208;&#176;&#208;&#185; 22 13:39 ..
-rw-r--r--  1 root root    0 &#208;&#188;&#208;&#176;&#208;&#185; 23 18:40 boinc_lockfile
-rw-r--r--  1 root root 8192 &#208;&#188;&#208;&#176;&#208;&#185; 23 18:40 boinc_mmap_file
-rw-r--r--  1 root root 5633 &#208;&#188;&#208;&#176;&#208;&#185; 23 18:40 init_data.xml
-rw-r--r--  1 root root  105 &#208;&#188;&#208;&#176;&#208;&#185; 23 18:40 job.xml
-rwxr-xr-x  1 root root 8546 &#208;&#188;&#208;&#176;&#208;&#185; 23 18:40 run_atlas
drwxrwx--x  2 root root 4096 &#208;&#188;&#208;&#176;&#208;&#185; 23 18:40 shared
-rw-r--r--  1 root root 1172 &#208;&#188;&#208;&#176;&#208;&#185; 23 18:41 stderr.txt
-rw-r--r--  1 root root  100 &#208;&#188;&#208;&#176;&#208;&#185; 23 18:40 wrapper_26015_x86_64-pc-linux-gnuparent process exit 2
child process exit 2
18:51:05 (30913): run_atlas exited; CPU time 1.770000
18:51:05 (30913): app exit status: 0x2
18:51:05 (30913): called boinc_finish(195)

</stderr_txt>
]]>
```
В дистрибутивах для x86_64 singularity уже есть. На машине **koakuma** этот дистрибутив, а также cvmfs развёрнут.

Работоспособность singularity можно проверить такой командой (подразумевается, что cvmfs в системе имеется):
```
singularity exec -B /cvmfs /cvmfs/atlas.cern.ch/repo/.images/singularity/x86_64-slc6.img hostname
```
В ответ данная команда должна выдать текущее имя хоста.

Под бинарным транслятором singularity пока не запускается. По этой проблеме открыты багрепорты:

* [bug 114325: rtc_opt_rel_p1_x64_ob v3.1: namespaces недоступны](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=114325) - решён в версии rtc 3.3;
* [bug 114822: prctl(PR_SET_NO_NEW_PRIVS, ...) не работает под бинарным транслятором](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=114822) - решён в версии rtc 3.3;
* [bug 117073: rtc.3.3: проблемы со сменой пользователя через su](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=117073) - решён в версии rtc 3.5;
* [bug 116955: unshare(CLONE_FS) не работает под бинарным транслятором](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=116955) - решён в отладочной версии rtc 3.3, **не решён в релизной**;
* [bug 120470: rtc-3.5: stat("/proc/self/exe") возвращает -1 (а также неизвестно, правильно ли возвращает st_mode и st_uid)](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=120470) - решён в версии rtc 4.0;

Рабочий вариант бинарного транслятора ожидается не ранее, чем выйдет ОС Эльбрус 6.3.

## Работа в нативном режиме

BOINC поддерживает режим [анонимной платформы](https://boinc.berkeley.edu/wiki/anonymous_platform). В этом режиме по очевидным причинам с серверов проектов нельзя будет скачивать бинарники для исполнения, клиент BOINC будет оперировать теми бинарниками, которые ему будут подложены, скачивая с сайтов проекта исключительно файлы заданий. Бинарники нужно будет собрать самостоятельно. 

В течение 2018-2021 года проводилось исследование работы в нативном режиме. Результаты неутешительны: для многих задач не существует исходных кодов для сборки; многие из тех, для которых исходные коды есть - возвращают неправильные результаты; те, которые возвращают правильные результаты - выполняются не быстрее (а иногда сильно дольше), чем в нативном режиме, а также нередко требуют серьёзной доработки. В связи с этим работа BOINC на "Эльбрусе" в нативном режиме признана нецелесообразной, и дальнейшие исследования ведутся исключительно по работе в транслируемом режиме. По этой причине вся информация дальше приведена исключительно с исторической целью.

В общем случае boinc запускается командой:
```
/usr/bin/boinc --daemon --dir /var/lib/boinc
```
Все пути даны по умолчанию:
* `/usr/bin/boinc` - путь к бинарнику BOINC;
* `/var/lib/boinc` - путь к рабочему каталогу BOINC.

"Красиво" (graceful) завершить работу клиента можно, дав команду менеджером:
```
boinccmd --quit
```
Скрипт `boinc_service`, приведённый выше, так и делает, автоматически определяя, работаем ли мы в нативном или в транслируемом режиме.

Сборка BOINC описана выше.

### Примеры проектов, поддерживающих режим анонимной платформы

Из упомянутых в начале статьи проектов такими проектами являются:
* RakeSearch (Rake search for Rank 10) - до завершения расчётов работал, имел официальное приложение для "Эльбрусов".
* Separation (Milkyway@home) - работает, но даёт неправильные результаты.
* N-Body (Milkyway@home) - работает.
* Gravitational Wave Search (Einstein@home) - работает, но даёт неправильные результаты.
* Binary Radio Pulsar Search (Einstein@home) - работает.
* SixTrack (LHC@home) - не получает задания.

Принципиально не могут работать:
* Period Search (Asteroids@home) - cудя по всему, не поддерживается, судя по [этой теме](http://asteroidsathome.net/boinc/forum_thread.php?id=728#6157) на форуме. Есть исходники самого расчётного приложения, но нет исходников адаптированной для BOINC версии.
* [planck_param_sims](https://github.com/marius311/lsplitsims) (Cosmology@Home) - требует docker, которого у нас пока нет ([bug 111934](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=111934)), а также, [судя по всему](https://www.cosmologyathome.org/faq.php#camb-legacy), и аппаратную виртуализацию.
* [camb_boinc2docker](https://github.com/marius311/camb_boinc2docker) (Cosmology@Home) - требует docker, которого у нас пока нет ([bug 111934](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=111934)), а также, [судя по всему](https://www.cosmologyathome.org/faq.php#camb-legacy), и аппаратную виртуализацию.
* camb_legacy (Cosmology@Home) - похоже, нет исходников. Есть что-то похожее [здесь](https://github.com/marius311/CAMB), но не собирается, говоря "ошибка: переменная цикла не найдена, цикл нельзя использовать в конструкции omp for".

Проекты Universe@home и LHC@home не имеют приложений с открытыми исходниками (кроме SixTrack у последнего).

### Работа с RakeSearch

В 2019-2020 годах вся работа велась по квадратам порядка 10.

#### Официальное приложение

С января 2020 года выпущено официальное приложение RakeSearch для платформы e2k-linux-gnu, таким образом, необходимость в самостоятельной сборке отпала.

Здесь руководство по сборке приведено в ознакомительных целях (например, если нужно собрать приложение для себя с целью снятия профиля, разборов информации от `perf top` и т.п.)

Если же это не нужно, то достаточно просто приаттачиться к проекту и задания начнут получаться автоматически.

В официальном приложении были две проблемы:

1. Архитектура, с которой оно собрано (`e2k-linux-gnu`), по умолчанию не совпадает с архитектурой BOINC (`e2k-mcst-linux-gnu`). Решить можно двумя способами:
* Конфигурировать сборку BOINC с параметром `--with-boinc-alt-platform=e2k-linux-gnu` (это сделает `e2k-linux-gnu` основной платформой для BOINC-а);
* Добавить в файл `/var/lib/boinc/cc_config.xml`, в блок `<options>` строчку `<alt_platform>e2k-linux-gnu</alt_platform>` (это позволит BOINC-у считать задания как для `e2k-mcst-linux-gnu`, так и для `e2k-linux-gnu`).

2. Почему-то не проходит проверка чексуммы скачанного бинарника приложения. Для того, чтобы обойти это, необходимо после аттача к проекту и автоматического скачивания бинарника (и появления сообщения типа "Signature verification failed for rakesearch10_3.1_e2k-linux-gnu" в логе сообщений клиента BOINC) завершить работу клиента BOINC, после чего в файле `/var/lib/boinc/client_state.xml` найти блок `<file>`, содержащий строчку `<name>rakesearch10_3.1_e2k-linux-gnu</name>`, и в нём `<status>-120</status>` поменять на `<status>1</status>`, после чего заново запустить клиент BOINC.

Далее описан процесс сборки текущих исходников (commit `04b4adb`) из репозитория RakeSearch; изменения, относящиеся к приложению для "Эльбруса", туда пока не внесены.

* Выкачиваем исходники:
```
git clone https://github.com/CrystalFrost/RakeSearch
cd RakeSearch
git checkout RakeSearchBOINC
cd RakeSearchV3/RakeDiagSearchV3/RakeDiagSearchV3
cp Makefile_x86-64 Makefile_e2k
```
* Устанавливаем переменную `BOINC_DIR` в файле `Makefile_e2k` так, чтобы она указывала на тот каталог, где собирался нативный BOINC (то есть тот, в котором лежит каталог `api`);

* Из файла `main.cpp` убираем UTF-8 BOM;

* Собираем:
```
make -j4 -f Makefile_e2k
```
* Копируем в каталог `/var/lib/boinc/projects/rake.boincfast.ru_rakesearch` (создав его при необходимости) получившийся файл `rakesearch` (подразумевается, что клиент BOINC настроен и работает, а также подключен к проекту RakeSearch, либо с помощью удалённого менеджера аккаунтов типа [BOINCstats BAM!](https://boincstats.com/en/bam/), либо вручную);

* Создаём там же файл `app_info.xml` следующего содержания:
```
<app_info>
  <app>
    <name>rakesearch10</name>
    <user_friendly_name>RakeSearch for rank 10</user_friendly_name>
  </app>
  <file_info>
    <name>rakesearch</name>
    <executable/>
  </file_info>
  <app_version>
    <app_name>rakesearch10</app_name>
    <version_num>702</version_num>
    <api_version>7.9.0</api_version>
    <file_ref>
      <file_name>rakesearch</file_name>
      <main_program/>
    </file_ref>
  </app_version>
</app_info>
```
После этого можно запускать BOINC и обновлять проект.

### Сборка приложений Milkyway@home

* Клонируем (поправленные для эльбруса) исходники: `git clone https://github.com/makise-homura/milkywayathome_client ; cd milkywayathome_client; git checkout elbrus-1.76` (на данный момент (октябрь 2021) workunit-ы посылаются для версии 1.76, а не 1.80 и выше, поэтому вместо ветки `elbrus`, являющейся модификацией ветки `master`, нужно забирать ветку `elbrus-1.76`);
* Скачиваем зависимости: `git submodule init ; git submodule update --recursive`;
* Собираем (без OpenCL - нам интересны вычисления на процессоре, а не видеокарте): `mkdir build ; cd build ; cmake -DSEPARATION_OPENCL=OFF -DNBODY_OPENCL=OFF .. ; make -j16`.
* Копируем бинарники из `build/bin` в каталог `/var/lib/boinc/projects/milkyway.cs.rpi.edu_milkyway`;
* Создаём файл `/var/lib/boinc/projects/milkyway.cs.rpi.edu_milkyway/app_info.xml` следующего содержания:
```
<app_info>
  <app>
    <name>milkyway</name>
    <user_friendly_name>Milkyway@home Separation</user_friendly_name>
  </app>
  <file_info>
    <name>milkyway_separation</name>
    <executable/>
  </file_info>
  <app_version>
    <app_name>milkyway</app_name>
    <version_num>146</version_num>
    <file_ref>
      <file_name>milkyway_separation</file_name>
      <main_program/>
    </file_ref>
  </app_version>
  <app>
    <name>milkyway_nbody</name>
    <user_friendly_name>Milkyway@home N-Body Simulation</user_friendly_name>
  </app>
  <file_info>
    <name>milkyway_nbody</name>
    <executable/>
  </file_info>
  <app_version>
    <app_name>milkyway_nbody</app_name>
    <version_num>182</version_num>
    <file_ref>
      <file_name>milkyway_nbody</file_name>
      <main_program/>
    </file_ref>
  </app_version>
</app_info>
```
* Перезапускаем BOINC и обновляем проект.

На данный момент приложение Separation неправильно считает математику, если скомпилировано в нативном режиме (под бинарным транслятором при этом всё работает так же, как на эталонной x86_64-машине), что приводит к провалу проверки сервером почти каждого сделанного workunit-а. Кроме того, оно выполняется существенно дольше транслируемого (5300 млрд. тактов против 3400). Поэтому для него при наличии на машине бинарного транслятора можно применить такой обход:

* Собираем на x86_64-машине бинарник этого приложения, указав в вызове CMake параметр `-DSEPARATION_STATIC`);

* Кладём этот бинарник в `/var/lib/boinc/projects/milkyway.cs.rpi.edu_milkyway` (здесь и далее считается, что путь к каталогу проекта именно такой, если это не так, его нужно заменить при выполнении этого алгоритма на актуальный) под именем `milkyway_static`;

* Создаём файл `milkyway_separation.с` следующего содержания (исправив путь к бинарному транслятору в строчке 7 и/или к бинарнику `milkyway_static` в строчке 11, если надо):
```
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    char **argv_rtc = (char **)malloc((argc + 5) * sizeof(char *));
    if(argv_rtc == NULL) return 1;
    argv_rtc[0] = "/opt/mcst/rtc/bin/rtc_opt_rel_p9_x64_ob";
    argv_rtc[1] = "--path_prefix";
    argv_rtc[2] = "/";
    argv_rtc[3] = "--";
    argv_rtc[4] = "/var/lib/boinc/projects/milkyway.cs.rpi.edu_milkyway/milkyway_static";
    for (int i = 1; i < argc; ++i) argv_rtc[+ i](4) = argv[i];
    argv_rtc[+ argc](4) = NULL;
    return execvp(argv_rtc[0], argv_rtc);
}
```
* Собираем его на эльбрусе командой `gcc milkyway_separation.с -o milkyway_separation` и тоже кладём бинарник в `/var/lib/boinc/projects/milkyway.cs.rpi.edu_milkyway`;

* Перезапускаем BOINC и обновляем проект.

Теперь с помощью бинарного транслятора будет вызываться транслируемый статический бинарник, а не нативный, возвращающий неверные результаты.

### Сборка SixTrack (LHC@home)

На старых версиях компилятора сборка до конца не проходит из-за [bug 114943](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=114943) и [bug 114938](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=114938). Необходмимо пользоваться компилятором версии 1.25 или более новой.

Клонируем куда-нибудь SixTrack и собираем (сначала собрав API BOINC):
```
git clone https://github.com/SixTrack/SixTrack.git
cd SixTrack
git submodule update --init lib/boinc/
cd lib
./buildBoinc.sh
cd ..
./cmake_six CR BOINC AVX
```
После сборки берём бинарник, имя которого начинается с `SixTrack`, например `SixTrack_50403-3cc8071_zlib_cr_boinc_crlibm_rn_Linux_gfortran_static_avx_e2k_64bit_double`, из каталога `build/SixTrack_cmakesix_AVX_BOINC_CR_defaultcompiler_defaultbuildtype` (или подобного в подкаталоге `build`), кладём его в каталог `/var/lib/boinc/projects/lhcathome.cern.ch_lhcathome` и создаём там же такой файл `app_info.xml`:
```
<app_info>
  <app>
  <name>sixtrack</name>
  </app>
  <file_info>
    <name>sixtrack</name>
    <executable/>
  </file_info>
  <app_version>
    <app_name>sixtrack</app_name>
    <version_num>50403</version_num>
    <api_version>7.14.2</api_version>
    <plan_class>avx</plan_class>
    <flops>100000000.000000</flops>
    <avg_ncpus>1.0</avg_ncpus>
    <file_ref>
      <file_name>sixtrack</file_name>
      <main_program/>
    </file_ref>
  </app_version>
</app_info>
```
Сервер при загрузке заданий может сыпать в лог сообщения типа:
```
Message from server: Your app_info.xml file doesn't have a usable version of CMS Simulation.
Message from server: Your app_info.xml file doesn't have a usable version of Theory Simulation.
Message from server: Your app_info.xml file doesn't have a usable version of ATLAS Simulation.
```
Чтобы их избежать, можно в [настройках места размещения](https://lhcathome.cern.ch/lhcathome/prefs.php?subset=project) выключить получение заданий для всех приложений, кроме SixTrack.

Ранее получение заданий не происходило нормально - сервер [возвращал ошибку](https://lhcathome.cern.ch/lhcathome/forum_thread.php?id=5561#43796). Сейчас (октябрь 2021) эта ошибка больше не повторяется, но причина её так и не была выяснена.

### Сборка приложений Einstein@home

Описание приложений Einstein@home приведено [здесь](https://einsteinathome.org/application-source-code-and-license).

Они используют библиотеки **fftw** и **gsl**.

**fftw 3.3.8** (должна собираться в двух вариантах: с поддержкой обычной и одинарной точности; собирается с ними очень долго - см. [bug 115330](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=115330), для поддержки SSE, SSE2, AVX и AVX2 также нужен [патч](https://raw.githubusercontent.com/makise-homura/boinc-for-oselbrus/master/fftw-avx-sse.patch)):
```
wget http://fftw.org/fftw-3.3.8.tar.gz
wget https://raw.githubusercontent.com/makise-homura/boinc-for-oselbrus/master/fftw-avx-sse.patch
tar xf fftw-3.3.8.tar.gz
cd fftw-3.3.8
patch -lp1 < ../fftw-avx-sse.patch
./configure --prefix=/usr --enable-openmp --enable-threads --enable-avx --enable-avx2 --enable-sse2 --enable-shared --enable-static
make -j20
make install
./configure --prefix=/usr --enable-openmp --enable-threads --enable-avx --enable-avx2 --enable-sse --enable-sse2 --enable-shared --enable-static --enable-float
make -j20
make install
cd ..
```
**gsl 1.15**:
```
wget http://ftpmirror.gnu.org/gsl/gsl-1.15.tar.gz
tar xf gsl-1.15.tar.gz
cd gsl-1.15
cp /usr/share/automake-1.14/config.{guess,sub} .
./configure --prefix=/usr
make -j20
make install
cd ..
```
#### Сборка приложения Gravitational Wave Search

Приложение Gravitational Wave Search собирается из пакета [LALSuite](https://wiki.ligo.org/Computing/LALSuite) (свежие исходники [здесь](http://software.ligo.org/lscsoft/source/lalsuite/)). Также, помимо LALSuite, нужно собрать некоторые дополнительные зависимости: **hdf5**, **cfitsio**, статическую библиотеку **curl**, **ldas-tools-al**, **chealpix**, **framecppc**, **ligo-libframe** и **ligo-metaio**.

Граф зависимостей выглядит так (по нему можно планировать порядок сборки):
```
fftw3 - fftw, собранная без float
fftw3f - fftw, собранная с float
lal <- hdf5, fftw3f, fftw3, gsl, boinc
lalsimulation <- lal, gsl
lalmetaio <- ligo-metaio, lal
lalburst <- gsl, ligo-metaio, lal, lalsimulation, lalmetaio
ldas-tools-al <- ligo-libframe
framecppc <- ldas-tools-al
lalframe <- lal, ligo-libframe, framecppc
cfitsio <- curl
chealpix <- cfitsio
lalpulsar <- gsl, fftw3, fftw3f, cfitsio, lal, boinc
lalinspiral <- gsl, lal, lalsimulation, ligo-libframe, lalframe, ligo-metaio, lalmetaio
lalinference <- gsl, hdf5, lal, lalsimulation, ligo-metaio, lalmetaio, lalburst, lalframe, chealpix, lalpulsar, lalispiral
lalapps <- gsl, fftw3, fftw3f, boinc, lal, lalsimulation, ligo-metaio, lalmetaio, ligo-libframe, lalframe, lalburst, cfitsio, lalpulsar, lalinspiral, lalinference
```
**hdf5 1.10.5** (собирается очень долго, см. [bug 114162](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=114162); по поводу пятой строчки см. [bug 114161](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=114161)):
```
wget https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.10/hdf5-1.10.5/src/hdf5-1.10.5.tar.gz
tar xf hdf5-1.10.5.tar.gz
cd hdf5-1.10.5
cp /usr/share/automake-1.14/config.{guess,sub} bin
sed -i 's/-Wsync-nand//' config/gnu-{flags,cxxflags} # см. bug 114161
./configure --prefix=/usr --enable-build-mode=production --enable-cxx
make -j20
make install
cd ..
```
**lal 6.20.1**:
```
wget http://software.ligo.org/lscsoft/source/lalsuite/lal-6.20.1.tar.xz
tar xf lal-6.20.1.tar.xz
cd lal-6.20.1
./configure --prefix=/usr --enable-boinc --disable-gcc-flags
make -j20
make install
cd ..
```
Если LAL не собирается, то могут помочь следующие вещи:
* В каталог `/usr/include/boinc` может потребоваться скопировать файл `config.h` из каталога сборки BOINC.
* `/usr/bin/python` должен указывать на тот интерпретатор Python, для которого в системе имеется модуль `numpy`. Для современных дистрибутивов его надо переделать на `/usr/bin/python3` вместо `/usr/bin/python2`.

**ldas-tools-al 2.6.2**:
```
wget http://software.ligo.org/lscsoft/source/ldas-tools-al-2.6.2.tar.gz
tar xf ldas-tools-al-2.6.2.tar.gz
cd ldas-tools-al-2.6.2
sed -i 's/#if __GNUC__ > 4 || ( __GNUC__ == 4 ) && ( __GNUC_MINOR__ >= 5 )/#if (__GNUC__ > 4 \|\| ( __GNUC__ == 4 ) \&\& ( __GNUC_MINOR__ >= 5 )) \&\& !defined(__e2k__)/' src/Deprecated.hh
./configure --prefix=/usr --disable-warnings-as-errors
make -j20
make install
cd ..
```
**framecpp 2.6.5**:
```
wget http://software.ligo.org/lscsoft/source/ldas-tools-framecpp-2.6.5.tar.gz
tar xf ldas-tools-framecpp-2.6.5.tar.gz
cd ldas-tools-framecpp-2.6.5
./configure --prefix=/usr --disable-warnings-as-errors
make -j20
make install
cd ..
```
**lalsimulation 1.9.0**:
```
wget http://software.ligo.org/lscsoft/source/lalsuite/lalsimulation-1.9.0.tar.xz
tar xf lalsimulation-1.9.0.tar.xz
cd lalsimulation-1.9.0
./configure --prefix=/usr --enable-openmp --disable-gcc-flags
make -j20
make install
cd ..
```
**ligo-metaio**:
```
git clone https://github.com/VolunteerComputingHelp/ligo-metaio
cd ligo-metaio
cp /usr/share/automake-1.14/config.{guess,sub} gnuscripts
sed -i 's/AM_CONFIG_HEADER/AC_CONFIG_HEADERS/' configure.ac
./configure --prefix=/usr
make -j20
make install
cd ..
```
После этого понадобится добавить включение `stdlib.h` и `stdio.h` в файл `/usr/include/metaio.h`, поскольку без этого не соберётся lalinspiral.

**lalmetaio 1.5.0**:
```
wget http://software.ligo.org/lscsoft/source/lalsuite/lalmetaio-1.5.0.tar.xz
tar xf lalmetaio-1.5.0.tar.xz
cd lalmetaio-1.5.0
./configure --prefix=/usr
make -j20
make install
cd ..
```
**lalburst 1.5.1**:
```
wget http://software.ligo.org/lscsoft/source/lalsuite/lalburst-1.5.1.tar.xz
tar xf lalburst-1.5.1.tar.xz
cd lalburst-1.5.1
./configure --prefix=/usr --disable-gcc-flags
make -j20
make install
cd ..
```
**ligo-libframe**:
```
git clone https://github.com/VolunteerComputingHelp/ligo-libframe
cd ligo-libframe
autoreconf -fi
./configure --prefix=/usr
make -j20
make install
cd ..
```
**lalframe 1.4.4**:
```
wget http://software.ligo.org/lscsoft/source/lalsuite/lalframe-1.4.4.tar.xz
tar xf lalframe-1.4.4.tar.xz
cd lalframe-1.4.4
./configure --prefix=/usr
make -j20
make install
cd ..
```
**chealpix 3.30.0**:
```
wget -O chealpix-3.30.0.tar.gz https://sourceforge.net/projects/healpix/files/Healpix_3.30/chealpix-3.30.0.tar.gz/download
tar xf chealpix-3.30.0.tar.gz
cd chealpix-3.30.0
cp /usr/share/automake-1.14/config.{guess,sub} .
CFITSIO_LIBS="-lcurl -lcfitsio" ./configure --prefix=/usr
make -j20
make install
cd ..
```
**lalinspiral 1.9.0**:
```
wget http://software.ligo.org/lscsoft/source/lalsuite/lalinspiral-1.9.0.tar.xz
tar xf lalinspiral-1.9.0.tar.xz
cd lalinspiral-1.9.0
./configure --prefix=/usr --enable-all-lal --enable-lalframe --disable-gcc-flags
make -j20
make install
cd ..
```
**curl 7.58.0** (его надо пересобрать со статической библиотекой, см. [bug 115238](http://bugzilla.lab.sun.mcst.ru/bugzilla-mcst/show_bug.cgi?id=115238)):
```
wget https://curl.haxx.se/download/curl-7.58.0.tar.gz
tar xf curl-7.58.0.tar.gz
cd curl-7.58.0
./configure --enable-static --disable-ldap --without-gssapi --prefix=/usr
make -j20
make install
cd ..
```
**cfitsio**:
```
git clone https://github.com/healpy/cfitsio
cd cfitsio
./configure --enable-sse2 --enable-ssse3 --prefix=/usr
make -j20
make install
cd ..
```
**lalpulsar-1.18.0** (к сожалению, поддержка SIMD написана здесь на ассемблере x86, поэтому придётся её отключить - её нельзя собрать под Эльбрус без переписывания; это четвёртая строчка):
```
wget http://software.ligo.org/lscsoft/source/lalsuite/lalpulsar-1.18.0.tar.xz
tar xf lalpulsar-1.18.0.tar.xz
cd lalpulsar-1.18.0
sed -i 's/LALSUITE_CHECK_SIMD/AM_CONDITIONAL([HAVE_SSE_COMPILER],[false])/' configure.ac
autoreconf -fi
CFITSIO_LIBS="-lcurl -lcfitsio" ./configure --prefix=/usr --enable-boinc --disable-gcc-flags --enable-openmp --enable-cfitsio
make -j20
make install
cd ..
```
**lalinference 1.11.0**:
```
wget http://software.ligo.org/lscsoft/source/lalsuite/lalinference-1.11.0.tar.xz
tar xf lalinference-1.11.0.tar.xz
cd lalinference-1.11.0
./configure --prefix=/usr --enable-openmp --enable-all-lal --disable-gcc-flags
make -j20
make install
cd ..
```
**lalapps 6.24.0** (точнее, не все LAL Apps, а только нужный нам бинарник и библиотеку для него):
```
wget http://software.ligo.org/lscsoft/source/lalsuite/lalapps-6.24.0.tar.xz
tar xf lalapps-6.24.0.tar.xz
cd lalapps-6.24.0
CFITSIO_LIBS="-lcfitsio -lcurl -licuuc -licudata -ldl -lstdc++" ./configure --prefix=/usr --enable-boinc --disable-gcc-flags
cd src/lalapps
make -j20
cd ../../src/pulsar/GCT
wget https://git.ligo.org/lscsoft/lalsuite-archive/raw/master/lalapps/src/pulsar/EinsteinAtHome/hs_boinc_extras.h
sed -i '1i#include <stdbool.h>' hs_boinc_extras.c
wget https://git.ligo.org/lscsoft/lalsuite-archive/raw/master/lalapps/src/pulsar/EinsteinAtHome/hs_boinc_options.h
wget https://raw.githubusercontent.com/lscsoft/lalsuite-archive/master/lalapps/src/pulsar/GCT/gc_hotloop_sse2.h
sed -i 's/-DEAH_BOINC/-DEAH_BOINC -DGC_SSE2_OPT -DEXP_NO_ASM /' Makefile
sed -i 's/-O2/-O3/' Makefile
make -j20 eah_HierarchSearchGCT
```
После этого получившийся файл `eah_HierarchSearchGCT` следует скопировать в `/var/lib/boinc/projects/einstein.phys.uwm.edu` и там же создать файл `app_info.xml` следующего содержания (либо добавить в него всё, что находится внутри тега `app_info`):
```
<app_info>
  <app>
    <name>einstein_O2MD1</name>
    <user_friendly_name>Gravitational Wave search O2 Multi-Directional</user_friendly_name>
  </app>
  <file_info>
    <name>eah_HierarchSearchGCT</name>
    <executable/>
  </file_info>
  <app_version>
    <app_name>einstein_O2MD1</app_name>
    <version_num>208</version_num>
    <plan_class>GWnew</plan_class>
    <api_version>7.3.0</api_version>
    <file_ref>
      <file_name>eah_HierarchSearchGCT</file_name>
      <main_program/>
    </file_ref>
  </app_version>
</app_info>
```
После этого нужно перезапустить BOINC.

Как видно, собранный файл подходит для задачи "Gravitational Wave search O2 Multi-Directional" (einstein_O2MD1) - единственной, которая считается на процессоре, а не GPU.

Стоит отметить, что на современных процессорах "Эльбрус-8С" работа данного приложения без поддержки SSE в LALapps длится порядка 16 суток, что больше дедлайна; **таким образом, ни один work unit не может быть отправлен в срок**. На "Эльбрус-8С2" подсчёт завершается за 13 суток, что чуть меньше дедлайна, но всё равно, при ненулевом даунтайме машины дедлайн может быть превышен. Поэтому было необходимо переписать поддержку SSE с ассемблера на builtin-ы. Это повысило производительность по результатам замеров примерно в 3 раза, что, хоть и в 7,67 раз медленнее x86_64 (2,67 раза с поправкой на тактовую частоту), но позволяет посчитать задание примерно за 5 суток, что укладывается в дедлайн 14 дней.

Для этого нужно следующим образом модифицировать процесс сборки **lalapps**: заменить строчки
```
wget https://raw.githubusercontent.com/lscsoft/lalsuite-archive/master/lalapps/src/pulsar/GCT/gc_hotloop_sse2.h
sed -i 's/-DEAH_BOINC/-DEAH_BOINC -DGC_SSE2_OPT -DEXP_NO_ASM /' Makefile
```
на
```
wget https://github.com/makise-homura/lalsuite-archive/raw/e2k/lalapps/src/pulsar/GCT/gc_hotloop_sse2.h
sed -i 's/-DEAH_BOINC/-DEAH_BOINC -DGC_SSE2_OPT /' Makefile
```
Готовый к сборке вариант lalapps можно найти [здесь](https://github.com/makise-homura/lalsuite-archive/tree/e2k). Там нужно собирать цель `eah_HierarchSearchGCT_SSE2`, а не `eah_HierarchSearchGCT`.

Также, возможно, если коллаборация LIGO примет [pull request](https://github.com/lscsoft/lalsuite-archive/pull/2), поддержка e2k появится и в апстриме ([здесь](https://github.com//lscsoft/lalsuite-archive/) и [здесь](https://git.ligo.org/lscsoft/lalsuite)).

#### Сборка приложения Вinary Radio Pulsar Search

Скачиваем [файл с исходниками](http://einstein.phys.uwm.edu/download/brp-src-release.zip), распаковываем, идём в каталог `src`.

Скачиваем файл `einsteinfixes.h`:
```
wget https://github.com/makise-homura/boinc-for-oselbrus/raw/master/einsteinfixes.h
```
Патчим исходники:
```
echo '#define ERP_GIT_VERSION "unknown (git repository not found!)"' > erp_git_version.h
sed -ie 's!#include "sysdep.h"!#include <boinc/config.h>\n#include <stdlib.h>\n#include <string.h>\n#include "einsteinfixes.h"\n#include <errno.h>\n#define _(x) x!' erp_execinfo_plus.c
```
Если нет файлов для профилирования, то не получится собрать бинарник с профилем. В таком случае отключаем генерацию профиля и собираем:
```
sed -i 's/-fprofile-use//' Makefile
LDFLAGS=-ldl make -j20 EINSTEIN_RADIO_INSTALL=/usr release
```
Однако, благодаря [этой теме](https://einsteinathome.org/ru/content/no-test-file-brp-src-releasezip), можно понять, как взять файлы генерации профиля.

Для удобства, архив с тестовыми файлами, а также соответствующим им патчем для `Makefile` (распаковывается в корень сборки приложения; патч применяется командой `patch -p1 < Makefile.patch`) выложен [здесь](https://github.com/makise-homura/boinc-for-oselbrus/raw/master/brp-profiles.tgz).

Если нужно сделать всё вручную, то надо действовать следующим образом.

Необходимо иметь хотя бы одну машину, на которой зарегистрирован проект Einstein@home, и где выполняются задачи приложения Вinary Radio Pulsar Search. Из каталога `/var/lib/boinc/projects/einstein.phys.uwm.edu/` нам нужны следующие файлы:
* `stochastic_full.bank`;
* Любой файл с расширением `.bin4`;
* Соответствующий ему файл с расширением `.zap` (нескольким файлам `.bin4` соответствует один файл с расширением `.zap`, имя которого совпадает с началом имени `.bin4`-файла).

Из первого из указанных файлов нужно выбрать короткую серию следующей командой:
```
head -n 100 /var/lib/boinc/projects/einstein.phys.uwm.edu/stochastic_full.bank > test/templates_400Hz_2_short.bank
```
Далее, редактируем `Makefile`, указывая:
* для параметра `-t` - путь к файлу `test/templates_400Hz_2_short.bank`;
* для параметра `-l` - путь к файлу с расширением `.zap`;
* для параметра `-i` - путь к файлу с расширением `.bin4`.

Когда файлы для профилирования положены в нужные места, а в Makefile прописан путь для них, можно собирать (сборка профилировочной информации занимает от 1 до 10 минут):
```
LDFLAGS=-ldl make EINSTEIN_RADIO_INSTALL=/usr profile
rm einsteinbinary
LDFLAGS=-ldl make EINSTEIN_RADIO_INSTALL=/usr release
```
Получившийся файл `einsteinbinary` нужно положить в `/var/lib/boinc/projects/einstein.phys.uwm.edu` и и там же создать файл `app_info.xml` следующего содержания (либо добавить в него всё, что находится внутри тега `app_info`):
```
<app_info>
  <app>
    <name>einsteinbinary_BRP4</name>
    <user_friendly_name>Binary Radio Pulsar Search (Arecibo) 1.00</user_friendly_name>
  </app>
  <file_info>
    <name>einsteinbinary</name>
    <executable/>
  </file_info>
  <app_version>
    <app_name>einsteinbinary_BRP4</app_name>
    <version_num>100</version_num>
    <file_ref>
      <file_name>einsteinbinary</file_name>
      <main_program/>
    </file_ref>
  </app_version>
</app_info>
```
После этого нужно перезапустить BOINC.
