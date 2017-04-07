ALL: peek poke

peek: peekpoke.c
	$(CC) $< -o $@

poke: peekpoke.c
	$(CC) $< -o $@
