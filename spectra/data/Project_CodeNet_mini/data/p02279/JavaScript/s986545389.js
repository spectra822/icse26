const line = require('fs').readFileSync('/dev/stdin', 'utf-8').split('\n');

const newNode = (id, arr) => {
    return {
        id: id,
        children: [...arr],
        parentNode: -1,
        depth: null
    };
};

const nodeToString = node => {
    const type = node.parentNode === -1 ? 'root'
               : node.children.length > 0 ? 'internal node'
               : 'leaf';
    const arr = `[${node.children.join(', ')}]`;
    return `node ${node.id}: parent = ${node.parentNode}, depth = ${node.depth}, ${type}, ${arr}`;
};

const setDepth = tree => {
    const root = tree.filter(x => x.parentNode === -1)[0];
    const helper = (node, n) => {
        node.depth = n;
        node.children.forEach(x => {
            helper(tree[x], n+1);
        });
    };
    helper(root, 0);
};

const n = parseInt(line[0]);
const data = line.slice(1, n+1)
                 .map(x => x.split(' ').map(Number));

const tree = data.map(x => {
    const id = x[0];
    const children = x.slice(2);
    return newNode(id, children);
});

tree.sort((a, b) => a.id - b.id);
tree.forEach((x, _, arr) => {
    x.children.forEach(y => {
        arr[y].parentNode = x.id;
    });
});

setDepth(tree);

console.log(tree.map(x => nodeToString(x)).join('\n'));

