
void main (int argc, char **argv) {
  Component p = $newComponent (initProducer, reactProducer);
  Component c = $newComponent (initConsumer, reactConsumer);
  List lis1 =listNewCell ((p));
  List lis2 =listNewCell ((c));
  List lis = $append (lis1, lis2);
  runQueue = lis;
$connect(p,c);
  Dispatcher ();
}

