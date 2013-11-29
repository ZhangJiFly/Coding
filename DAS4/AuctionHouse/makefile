JFLAGS = -g
JC = javac
.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
		Client/AuctionClient.java \
		Client/AuctionClientIntf.java \
		Server/AuctionServer.java \
		Server/AuctionServerIntf.java \
		Server/MyTimer.java \
		Server/AuctionItem.java \
		Server/Bid.java \

default: classes

classes: $(CLASSES:.java=.class)

clean:
		$(RM) Client/*.class
		$(RM) Server/*.class