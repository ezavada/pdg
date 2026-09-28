'use strict';

// Intrusive list used by the legacy JSC timer shim. This is local to that
// runtime because current Node's internal list no longer includes shift(),
// while the timer shim still requires it.

function init(list) {
  list._idleNext = list;
  list._idlePrev = list;
  return list;
}

function peek(list) {
  return list._idlePrev === list ? null : list._idlePrev;
}

function remove(item) {
  if (item._idleNext) item._idleNext._idlePrev = item._idlePrev;
  if (item._idlePrev) item._idlePrev._idleNext = item._idleNext;
  item._idleNext = null;
  item._idlePrev = null;
}

function append(list, item) {
  if (item._idleNext || item._idlePrev) remove(item);
  item._idleNext = list._idleNext;
  item._idlePrev = list;
  list._idleNext._idlePrev = item;
  list._idleNext = item;
}

function shift(list) {
  var item = peek(list);
  if (item) remove(item);
  return item;
}

function isEmpty(list) {
  return list._idleNext === list;
}

module.exports = {
  init: init,
  peek: peek,
  remove: remove,
  append: append,
  shift: shift,
  isEmpty: isEmpty
};
