#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h> // notice this! you need it! (windows)
// #include <unistd.h> // notice this! you need it (linux)!

typedef struct Client Client;
typedef struct Monitor Monitor;

static void detach(Client *c);
static void detachstack(Client *c);
static void attach(Client *c);
static void attachstack(Client *c);

struct Client {
	char name[256];
	float mina, maxa;
	int x, y, w, h;
	int oldx, oldy, oldw, oldh;
	int basew, baseh, incw, inch, maxw, maxh, minw, minh, hintsvalid;
	int bw, oldbw;

	int isfixed, isfloating, isurgent, neverfocus, oldstate, isfullscreen;
	Client *next;
	Client *snext;
	
	Monitor *mon;
	//Window win;
};

struct Monitor {
	char ltsymbol[16];
	float mfact;
	int nmaster;
	int num;
	int by;               /* bar geometry */
	int mx, my, mw, mh;   /* screen size */
	int wx, wy, ww, wh;   /* window area  */
	unsigned int seltags;
	unsigned int sellt;
	unsigned int tagset[2];
	int showbar;
	int topbar;
	Client *clients;
	Client *sel;
	Client *stack;
	Monitor *next;
	//Window barwin;
	//const Layout *lt[2];
};


void
detach(Client *c)
{
	Client **tc;
	for (tc = &c->mon->clients; *tc && *tc != c; tc = &(*tc)->next);
	*tc = c->next;
}

void
detachstack(Client *c)
{
	Client **tc, *t;

	for (tc = &c->mon->stack; *tc && *tc != c; tc = &(*tc)->snext);
	*tc = c->snext;

	//if (c == c->mon->sel) {
	//	for (t = c->mon->stack; t && !ISVISIBLE(t); t = t->snext);
	//	c->mon->sel = t;
	//}
}

void
attach(Client *c)
{
	c->next = c->mon->clients;
	c->mon->clients = c;
}

void
attachstack(Client *c)
{
	c->snext = c->mon->stack;
	c->mon->stack = c;
}

void *
ecalloc(size_t nmemb, size_t size)
{
    void *p;

    /* If memory could not be allocated then call die to exit the window manager. */
    if (!(p = calloc(nmemb, size)))
        //die("calloc:");
		printf("calloc...");
	printf("\nMemory allocated...");
    return p;
}

void
manage()
{
	Client *c, *t = NULL;
	c = ecalloc(1, sizeof(Client));
	//c->win = w;
	/* geometry */
	//c->x = c->oldx = wa->x;
	//c->y = c->oldy = wa->y;
	//c->w = c->oldw = wa->width;
	//c->h = c->oldh = wa->height;
	//c->oldbw = wa->border_width;

	strcpy(c->name, "test");

	//c->mon = t->mon;
	//c->tags = t->tags;

	//c->mon = selmon;

	// ...

	attach(c);
	//attachstack(c);

	//XChangeProperty(dpy, root, netatom[NetClientList], XA_WINDOW, 32, PropModeAppend,
	//	(unsigned char *) &(c->win), 1);
	//XMoveResizeWindow(dpy, c->win, c->x + 2 * sw, c->y, c->w, c->h); /* some windows require this */
	//setclientstate(c, NormalState);
	//if (c->mon == selmon)
	//	unfocus(selmon->sel, 0);
	c->mon->sel = c;
	//arrange(c->mon);
	//XMapWindow(dpy, c->win);
	//focus(NULL);
}

Monitor *
createmon(void)
{
	Monitor *m;

	m = ecalloc(1, sizeof(Monitor));
	//m->tagset[0] = m->tagset[1] = 1;
	//m->mfact = mfact;
	//m->nmaster = nmaster;
	//m->showbar = showbar;
	//m->topbar = topbar;
	//m->lt[0] = &layouts[0];
	//m->lt[1] = &layouts[1 % LENGTH(layouts)];
	//strncpy(m->ltsymbol, layouts[0].symbol, sizeof m->ltsymbol);
	m->topbar = 1;

	return m;
}

void
unmanage(Client *c)
{
	detach(c);
	free(c);
}

void display(struct Client* node){
    printf("\nLinked Client List: ");
    // as linked list will end when Node is Null
    while(node!=NULL){
        printf("%s, ",node->name);
        node = node->next;
    }
    printf("\n");
}

void displayStack(struct Client* node){
    printf("Linked Client Stack List: ");
    // as linked list will end when Node is Null
    while(node!=NULL){
        printf("%s, ",node->name);
        node = node->snext;
    }
    printf("\n");
}

int main()
{
	Monitor *m;
	printf("Start manage");
	m = createmon();

	//Client *c, *t = NULL;
	Client *c, *c2, *c3 = NULL;
	c = ecalloc(1, sizeof(Client));
	strcpy(c->name, "client1");
	c->mon = m;
	attach(c);
	attachstack(c);
	printf("\nAttached...");
	c->mon->sel = c;
	//manage();
	printf("\nManage Done...\n");

	c2 = ecalloc(1, sizeof(Client));
	strcpy(c2->name, "client2");
	c2->mon = m;
	attach(c2);
	attachstack(c2);
	printf("\nAttached 2...");
	c2->mon->sel = c2;

	c3 = ecalloc(1, sizeof(Client));
	strcpy(c3->name, "client3");
	c3->mon = m;
	attach(c3);
	attachstack(c3);
	printf("\nAttached 3...");
	c3->mon->sel = c3;

	//printf("\nName of client 1: %s", c->name);
	//printf("\nName of client 1 next: %s", c->next->name);
	//printf("\nName of client 2: %s", c2->name);
	//printf("\nName of client 2 next: %s", c2->next->name);
	//printf("\nName of client 3: %s", c3->name);
	//printf("\nName of client 3 next: %s", c3->next->name);

	display(c3);
	displayStack(c3);

	unmanage(c2);
	display(c3);

	unmanage(c3);
	display(c);

	// sleep(2); // for linux
	//Sleep(2000);

	printf("\nStart unmanage");
	unmanage(c);
	//unmanage(c2);
	//unmanage(c3);
	printf("\nUnmanaged Done...\n");

	if (!c && !c2) printf("Clients are nulled...");

	free(m);


	printf("\nBIT TESTING...\n");

	/*
	 *    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
	 *
	 * In the keys array where the macro is used we can tell that for tag 5 the value of
	 * 1 is shifted leftwards 4 times.
	 *
	 *    	TAGKEYS(                        XK_5,                      4)
	 *
	 * 1 << 4 becomes 000010000 in binary.
	 */

	/* unsigned int test = (1 << 8); // tag 9: 100000000 */
	/* unsigned int test = (1 << 6); // tag 7: 1000000 */
	/* unsigned int test = (1 << 4); // tag 5: 10000 */
	/* unsigned int test = (1 << 2); // tag 3: 100 */
	/* unsigned int test = (1 << 0); // tag 1: 1 */

	unsigned int test = (1 << 7); // tag 8: 10000000
	/* unsigned int test = (1 << 5); // tag 6: 100000 */
	/* unsigned int test = (1 << 3); // tag 4: 1000 */
	/* unsigned int test = (1 << 1); // tag 2: 10 */

	/* unsigned int test2 = (test & 01010); */
	unsigned int test2 = (test & 010101);

	printf("\ntest: %d", test);
	printf("\ntest2: %d", test2);

	printf("\nEND OF PROGRAM");

}
