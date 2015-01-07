#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int	peb_send_msg(char *mac_add,/* int chan,*/ char *from, char *msg, int type)
{
	struct sockaddr_rc	addr = { 0 };
	int					sock = 0,
						status = 0;
	char				data[] = "\x00\x18\x0b\xb8\x02\x05salut\x02yo\x0d\x31\x34\x32\x30\x36\x34\x34\x34\x34\x36\x30\x30\x30";
/*
		\x00
		\x18
		\x0b\xb8 -> endpoint: notification
		\x05 -> type (5 = sms, 2 = facebook)
		\x05salut
		\x02yo
		\x0d
		\x31
		\x34
		\x32
		\x30
		\x36
		\x34
		\x34
		\x34
		\x34
		\x36
		\x30
		\x30
		\x30
*/
	sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t)1; //chan;
	str2ba(mac_add, &addr.rc_bdaddr);
	status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
	if( status < 0)
		return (-1);
	status = write(sock, data, sizeof(data));
	close(sock);
}

int	main(int ac, char **av)
{
	char mac_add[18] = "";
	if (peb_send_msg(mac_add, NULL, NULL, 0) < 0)
		perror("[peb_error] ");
	return (0);
}
