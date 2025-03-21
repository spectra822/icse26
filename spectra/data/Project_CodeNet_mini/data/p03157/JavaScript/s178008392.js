/*! path: src/contest/atcoder/aising2019/c.ts */
/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./src/contest/atcoder/aising2019/c.ts");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./node_modules/webpack/buildin/module.js":
/*!***********************************!*\
  !*** (webpack)/buildin/module.js ***!
  \***********************************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = function(module) {
	if (!module.webpackPolyfill) {
		module.deprecate = function() {};
		module.paths = [];
		// module.parent = undefined by default
		if (!module.children) module.children = [];
		Object.defineProperty(module, "loaded", {
			enumerable: true,
			get: function() {
				return module.l;
			}
		});
		Object.defineProperty(module, "id", {
			enumerable: true,
			get: function() {
				return module.i;
			}
		});
		module.webpackPolyfill = 1;
	}
	return module;
};


/***/ }),

/***/ "./src/contest/atcoder/aising2019/c.ts":
/*!*********************************************!*\
  !*** ./src/contest/atcoder/aising2019/c.ts ***!
  \*********************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
/* WEBPACK VAR INJECTION */(function(module) {
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.main = void 0;
const fs_1 = __importDefault(__webpack_require__(/*! fs */ "fs"));
const io_1 = __webpack_require__(/*! ../../common/io */ "./src/contest/common/io.ts");
const uf_1 = __webpack_require__(/*! ../../common/uf */ "./src/contest/common/uf.ts");
const vr = [1, 0];
const vc = [0, 1];
function solve({ H, W, S }) {
    const uf = new uf_1.UnionFind(H * W);
    for (let r = 0; r < H; r++) {
        for (let c = 0; c < W; c++) {
            const id = r * W + c;
            for (let i = 0; i < 2; i++) {
                const nr = r + vr[i];
                const nc = c + vc[i];
                if (nr < H && nc < W) {
                    const nid = nr * W + nc;
                    if (S[r][c] !== S[nr][nc]) {
                        uf.union(id, nid);
                    }
                }
            }
        }
    }
    const dark = new Map();
    const light = new Map();
    for (let r = 0; r < H; r++) {
        for (let c = 0; c < W; c++) {
            const id = r * W + c;
            const root = uf.root(id);
            if (S[r][c] === '#') {
                dark.set(root, 1 + (dark.get(root) || 0));
            }
            else {
                light.set(root, 1 + (light.get(root) || 0));
            }
        }
    }
    let ans = 0;
    for (const root of dark.keys()) {
        const dc = dark.get(root);
        const lc = light.get(root) || 0;
        ans += dc * lc;
    }
    return ans;
}
function main(line) {
    const next = io_1.getNext(line);
    const H = parseInt(next());
    const W = parseInt(next());
    const S = [];
    for (let i = 0; i < H; i++) {
        S[i] = next();
    }
    console.log(solve({ H, W, S }));
}
exports.main = main;
if (__webpack_require__.c[__webpack_require__.s] === module) {
    const line = fs_1.default.readFileSync("/dev/stdin", "utf8");
    main(line);
}

/* WEBPACK VAR INJECTION */}.call(this, __webpack_require__(/*! ./../../../../node_modules/webpack/buildin/module.js */ "./node_modules/webpack/buildin/module.js")(module)))

/***/ }),

/***/ "./src/contest/common/io.ts":
/*!**********************************!*\
  !*** ./src/contest/common/io.ts ***!
  \**********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

Object.defineProperty(exports, "__esModule", { value: true });
exports.getNextBigInt = exports.getNextInt = exports.getNext = exports.getIteratorWithParser = exports.getIterator = void 0;
function* getIterator(line) {
    const tokens = line.split(/\s+/);
    for (const token of tokens) {
        yield token;
    }
}
exports.getIterator = getIterator;
function* getIteratorWithParser(line, parser) {
    const tokens = line.split(/\s+/);
    for (const token of tokens) {
        yield parser(token);
    }
}
exports.getIteratorWithParser = getIteratorWithParser;
function getNext(line) {
    const it = getIterator(line);
    return () => it.next().value;
}
exports.getNext = getNext;
function getNextInt(line) {
    const it = getIterator(line);
    return () => parseInt(it.next().value);
}
exports.getNextInt = getNextInt;
function getNextBigInt(line) {
    const it = getIterator(line);
    return () => BigInt(it.next().value);
}
exports.getNextBigInt = getNextBigInt;


/***/ }),

/***/ "./src/contest/common/uf.ts":
/*!**********************************!*\
  !*** ./src/contest/common/uf.ts ***!
  \**********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

Object.defineProperty(exports, "__esModule", { value: true });
exports.UnionFind = void 0;
class UnionFind {
    constructor(n) {
        this.v = new Array(n);
        this.v.fill(-1);
    }
    union(a, b) {
        if (!this.find(a, b)) {
            const ra = this.root(a);
            const rb = this.root(b);
            if (this.size(ra) > this.size(rb)) {
                this.v[ra] += this.v[rb];
                this.v[rb] = ra;
            }
            else {
                this.v[rb] += this.v[ra];
                this.v[ra] = rb;
            }
        }
    }
    find(a, b) {
        return this.root(a) === this.root(b);
    }
    root(a) {
        if (this.v[a] < 0) {
            return a;
        }
        this.v[a] = this.root(this.v[a]);
        return this.v[a];
    }
    size(a) {
        return -this.v[this.root(a)];
    }
}
exports.UnionFind = UnionFind;


/***/ }),

/***/ "fs":
/*!*********************!*\
  !*** external "fs" ***!
  \*********************/
/*! no static exports found */
/***/ (function(module, exports) {

module.exports = require("fs");

/***/ })

/******/ });
//# sourceMappingURL=submit.js.map