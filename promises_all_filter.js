_validateCollectionMulti(userId, collectionIds, becomeId = -1) {
    if (!Array.isArray(collectionIds)) {
        if (isNaN(parseInt(collectionIds, 10))) {
            throw {
                status: 404,
                message: `Invalid collection ids: ${collectionIds}`,
            };
        }
    } else {
        let self = this;
        let promises = [];
        for (let j of collectionIds) {
            promises.push(self._validateCollection(userId, j, becomeId));
        }
        return Q.all(promises).then(function (values) {
            return values.reduce((acc, curr, idx) => {
                acc.push(curr.collection_id);
                return acc;
            }, []);
        });
    }
}