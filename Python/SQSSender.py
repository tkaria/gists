from __future__ import print_function

import boto3
import botocore

SQS_CLIENT = boto3.resource('sqs')
try:
    # queue = SQS_CLIENT.create_queue(QueueName='ventureiq-lambda-pipeline')
    queue = SQS_CLIENT.get_queue_by_name(QueueName='ventureiq-lambda-pipeline')
    # with open('/tmp/github.com-123.json') as inputJSON:
    #     file_contents = inputJSON.read()
    key = 'github.com-123.json'
    bucket = 'ventureiq-site-2'
    queue.send_message(MessageBody='IGNORE', MessageAttributes={
        'key': {
            'DataType': 'String',
            'StringValue': key
        },
        'bucket': {
            'DataType': 'String',
            'StringValue': bucket
        }})
except botocore.exceptions.ClientError, e:
    print('Error: {}'.format(str(e)))

print(queue)
