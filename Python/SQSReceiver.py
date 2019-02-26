from __future__ import print_function

import boto3
import botocore

SQS_CLIENT=boto3.resource('sqs')
try:
    # queue = SQS_CLIENT.create_queue(QueueName='ventureiq-lambda-pipeline')
    queue = SQS_CLIENT.get_queue_by_name(QueueName='ventureiq-lambda-pipeline')
    for message in queue.receive_messages():
        print(message.body)
except:
    print('Error: {}'.format(str(queue)))

print(queue)