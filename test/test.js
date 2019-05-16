const assert = require('assert')
const getIsQuietHours = require('../lib/index').getIsQuietHours

if (process.platform !== 'win32') {
  assert.throws(getIsQuietHours)
} else {
  const isQuietHours = getIsQuietHours()
  const ok = isQuietHours === false || isQuietHours === true
  assert.ok(ok, true)
}
